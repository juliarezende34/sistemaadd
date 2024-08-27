#ifndef QUESTAO2_HPP
#define QUESTAO2_HPP

#include "../include.hpp"

void listarDoencas(unique_ptr<sql::Connection>& connection){
    // Cria um objeto do comando SQL
    unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement("SELECT * from doencas"));

    // Executa o comando
    unique_ptr<sql::ResultSet> result(statement->executeQuery());

    while(result->next()){
        cout << result->getString("cid") << "  ";
        cout << result->getString("nome_tecnico") << "  ";
        cout << result->getInt("id_patogeno") << "  \n";
        //doencas.push_back(doenca);
    }
}

void imprimirDoencas(unique_ptr<sql::Connection>& connection){
    cout << left << setw(20) << "CID" 
             << setw(30) << "Nome Técnico" 
             << setw(10) << "ID Patógeno" << endl;

        cout << string(55, '-') << endl; // Separador de linhas
    listarDoencas(connection);

    /*for (const auto& doenca : doencas) {
        int tamanho = doenca.nome_tecnico.length();
        cout << left << setw(20) << doenca.cid 
                << setw(30) << doenca.nome_tecnico 
                << setw(25) << doenca.id_patogeno << endl;
    }*/
}

void consultaCID(unique_ptr<sql::Connection>& connection){
    string cid;
    cout << "\nDigite o CID:\n>";
    cin.ignore();
    getline(cin,cid);
    string sql = R"(SELECT d.cid, d.nome_tecnico, np.nome AS "nome popular", p.nome_cientifico, p.tipo, GROUP_CONCAT(s.nome SEPARATOR ', ') AS "sintomas"
                    FROM doencas AS d
                    LEFT JOIN doenca_sintoma as ds ON d.cid = ds.id_doenca
                    LEFT JOIN sintomas AS s ON ds.id_sintoma = s.id
                    LEFT JOIN nome_popular AS np ON np.id_doenca = d.cid
                    LEFT JOIN patogenos AS p ON p.id = d.id_patogeno

                    WHERE d.cid = ?;

                    GROUP BY d.cid, d.nome_tecnico, np.nome, p.nome_cientifico, p.tipo;)";

    unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));
    statement->setString(1, cid);

    unique_ptr<sql::ResultSet> result(statement->executeQuery());

    while(result->next()){
        cout << result->getString("cid") << " | ";
        cout << result->getString("nome_tecnico") << " | ";
        cout << result->getString("nome popular") << " | ";
        cout << result->getString("nome_cientifico") << " | ";
        cout << result->getString("tipo") << " | ";
        cout << result->getString("sintomas") << " | \n";
        //doencas.push_back(doenca);
    }    
}

void consultaNomeTecnico(unique_ptr<sql::Connection>& connection){
    string nome;
    cout << "\nDigite o nome técnico:\n>";
    cin.ignore();
    getline(cin,nome);
    string sql = R"(SELECT d.cid, d.nome_tecnico, np.nome AS "nome popular", p.nome_cientifico, p.tipo, GROUP_CONCAT(s.nome SEPARATOR ', ') AS "sintomas"
                    FROM doencas AS d
                    LEFT JOIN doenca_sintoma as ds ON d.cid = ds.id_doenca
                    LEFT JOIN sintomas AS s ON ds.id_sintoma = s.id
                    LEFT JOIN nome_popular AS np ON np.id_doenca = d.cid
                    LEFT JOIN patogenos AS p ON p.id = d.id_patogeno

                    WHERE d.nome_tecnico = ?;

                    GROUP BY d.cid, d.nome_tecnico, np.nome, p.nome_cientifico, p.tipo;)";

    unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));
    statement->setString(1, nome);

    unique_ptr<sql::ResultSet> result(statement->executeQuery());

    while(result->next()){
        cout << result->getString("cid") << " | ";
        cout << result->getString("nome_tecnico") << " | ";
        cout << result->getString("nome popular") << " | ";
        cout << result->getString("nome_cientifico") << " | ";
        cout << result->getString("tipo") << " | ";
        cout << result->getString("sintomas") << " | \n";
        //doencas.push_back(doenca);
    }    
}

void consultaNomePopular(unique_ptr<sql::Connection>& connection){
    string nome;
    cout << "\nDigite o nome popular:\n>";
    cin.ignore();
    getline(cin,nome);
    string sql = R"(SELECT d.cid, d.nome_tecnico, np.nome AS "nome popular", p.nome_cientifico, p.tipo, GROUP_CONCAT(s.nome SEPARATOR ', ') AS "sintomas"
                    FROM doencas AS d
                    LEFT JOIN doenca_sintoma as ds ON d.cid = ds.id_doenca
                    LEFT JOIN sintomas AS s ON ds.id_sintoma = s.id
                    LEFT JOIN nome_popular AS np ON np.id_doenca = d.cid
                    LEFT JOIN patogenos AS p ON p.id = d.id_patogeno

                    WHERE np.nome = ?;

                    GROUP BY d.cid, d.nome_tecnico, np.nome, p.nome_cientifico, p.tipo;)";

    unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));
    statement->setString(1, nome);

    unique_ptr<sql::ResultSet> result(statement->executeQuery());

    while(result->next()){
        cout << result->getString("cid") << " | ";
        cout << result->getString("nome_tecnico") << " | ";
        cout << result->getString("nome popular") << " | ";
        cout << result->getString("nome_cientifico") << " | ";
        cout << result->getString("tipo") << " | ";
        cout << result->getString("sintomas") << " | \n";
        //doencas.push_back(doenca);
    }    
}

void consultaPatogeno(unique_ptr<sql::Connection>& connection){
    string nome;
    cout << "\nDigite o nome do patógeno:\n>";
    cin.ignore();
    getline(cin,nome);
    string sql = R"(SELECT d.cid, d.nome_tecnico, np.nome AS "nome popular", p.nome_cientifico, p.tipo, GROUP_CONCAT(s.nome SEPARATOR ', ') AS "sintomas"
                    FROM doencas AS d
                    LEFT JOIN doenca_sintoma as ds ON d.cid = ds.id_doenca
                    LEFT JOIN sintomas AS s ON ds.id_sintoma = s.id
                    LEFT JOIN nome_popular AS np ON np.id_doenca = d.cid
                    LEFT JOIN patogenos AS p ON p.id = d.id_patogeno

                    WHERE p.nome_cientifico = ?;

                    GROUP BY d.cid, d.nome_tecnico, np.nome, p.nome_cientifico, p.tipo;)";

    unique_ptr<sql::PreparedStatement> statement(connection->prepareStatement(sql));
    statement->setString(1, nome);

    unique_ptr<sql::ResultSet> result(statement->executeQuery());

    while(result->next()){
        cout << result->getString("cid") << " | ";
        cout << result->getString("nome_tecnico") << " | ";
        cout << result->getString("nome popular") << " | ";
        cout << result->getString("nome_cientifico") << " | ";
        cout << result->getString("tipo") << " | ";
        cout << result->getString("sintomas") << " | \n";
        //doencas.push_back(doenca);
    }    
}

void consultaEspecifica(unique_ptr<sql::Connection>& connection){
    int modo=-1;
    cout << "\nDigite o modo de pesquisa específica:\n[1] CID\n[2] Nome técnico\n[3] Nome popular\n[4] Patógeno\n[0] Sair\n>";
    cin >> modo;
    switch(modo){
        case 1:
            consultaCID(connection);
        break;

        case 2:
            consultaNomeTecnico(connection);
        break;

        case 3:
            consultaNomePopular(connection);
        break;

        case 4:
            consultaPatogeno(connection);
        break;

        case 0:
        break;
    }
    
}

#endif