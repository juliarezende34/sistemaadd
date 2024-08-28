#ifndef QUESTAO3_HPP
#define QUESTAO3_HPP

#include "../include.hpp"
#include "questao2.hpp"

void consultaDoencasComSintomas(unique_ptr<sql::Connection>& connection) {

    vector<string> sintomas;
    string sintoma;
    char continuar;

    do {
        cout << "Digite um sintoma: ";
        cin.ignore();
        getline(cin, sintoma);
        sintomas.push_back(sintoma);

        cout << "Deseja adicionar outro sintoma? (s/n): ";
        cin >> continuar;

    } while (continuar == 's' || continuar == 'S');


    // Construir a lista de sintomas para a consulta
    stringstream sintomasStream;
    for (size_t i = 0; i < sintomas.size(); ++i) {
        sintomasStream << "'" << sintomas[i] << "'";
        if (i < sintomas.size() - 1) {
            sintomasStream << ", ";
        }
    }

    // Construir a parte da consulta SQL 
    string sql = R"(
        SELECT 
            d.cid, 
            d.nome_tecnico AS nome_doenca, 
            SUM(
                CASE WHEN s.nome IN ()";
    sql += sintomasStream.str();
    sql += R"() THEN
                    CASE 
                        WHEN ds.nivel_ocorrencia = 'Muito comum' THEN 5
                        WHEN ds.nivel_ocorrencia = 'Comum' THEN 4
                        WHEN ds.nivel_ocorrencia = 'Pouco comum' THEN 3
                        WHEN ds.nivel_ocorrencia = 'Raro' THEN 2
                        WHEN ds.nivel_ocorrencia = 'Muito raro' THEN 1
                        ELSE 0 
                    END
                ELSE 0
                END
            ) - (
                SELECT COUNT(*)
                FROM (
    )";

    for (size_t i = 0; i < sintomas.size(); ++i) {
        sql += "SELECT '" + sintomas[i] + "' AS sintoma";
        if (i < sintomas.size() - 1) {
            sql += " UNION ALL ";
        }
    }

    sql += R"(
                ) AS lista_sintomas
                WHERE lista_sintomas.sintoma NOT IN (
                    SELECT s.nome 
                    FROM doenca_sintoma AS ds
                    JOIN sintomas AS s ON ds.id_sintoma = s.id
                    WHERE ds.id_doenca = d.cid
                )
            ) AS pontuacao
        FROM 
            doencas AS d
        LEFT JOIN 
            doenca_sintoma AS ds ON ds.id_doenca = d.cid
        LEFT JOIN 
            sintomas AS s ON ds.id_sintoma = s.id
        GROUP BY 
            d.cid
        ORDER BY 
            pontuacao DESC;
    )";

    unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));
    unique_ptr<sql::ResultSet> result(statement->executeQuery());

    int count=0, resultPage=8;
    string aux, resposta;
    cout << endl << endl;

    while (result->next()) {

        cout << left << setw(20) << "CID" << setw(30) << "Nome da Doença" << setw(10) << "Pontuação" << endl; 
        cout << string(60, '-') << endl;

        do{
            cout << setw(20) << result->getString("cid") << setw(35);
            cout << result->getString("nome_doenca");
            cout << result->getInt("pontuacao") << endl;
            count++;

            if (count == resultPage) {
                count = 0;
                cin.ignore();
                cout << "Pressione 'p' para ver mais resultados...\n";
                cin >> aux;
            }

        } while(result->next());
    }

    cout << "\nDeseja selecionar alguma doença? (s/n):\n>";
    cin >> resposta;

    if (resposta == "s" || resposta == "S"){
        consultaCID(connection);
    }

}


#endif