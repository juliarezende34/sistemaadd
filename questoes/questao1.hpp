#ifndef QUESTAO1_HPP
#define QUESTAO1_HPP
#include "../include.hpp"

void cadastrarDoenca(unique_ptr<sql::Connection>& connection) {
    string cid, nome_tecnico, nome_popular, nivel_ocorrencia;
    int id_patogeno, n_sintomas, n_nomes_populares;

    cout << "Digite o CID da doença: ";
    cin >> cid;

    cout << "Digite o nome técnico da doença: ";
    cin.ignore();
    getline(cin, nome_tecnico);

    cout << "Digite o ID do patógeno: ";
    cin >> id_patogeno;

    // Inserir doença na tabela doencas
    string query = "INSERT INTO doencas (cid, nome_tecnico, id_patogeno) VALUES (?, ?, ?)";
    unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));
    pstmt->setString(1, cid);
    pstmt->setString(2, nome_tecnico);
    pstmt->setInt(3, id_patogeno);

    try {
        pstmt->execute();
        cout << "Doença inserida com sucesso!\n";
    } catch (sql::SQLException &e) {
        cerr << "Erro ao inserir doença: " << e.what() << endl;
        return;
    }

    // Inserir nomes populares
    cout << "Quantos nomes populares deseja inserir? ";
    cin >> n_nomes_populares;
    cin.ignore();

    for (int i = 0; i < n_nomes_populares; i++) {
        cout << "Digite o nome popular: ";
        getline(cin, nome_popular);

        query = "INSERT INTO nome_popular (id_doenca, nome) VALUES (LAST_INSERT_ID(), ?)";
        pstmt.reset(connection->prepareStatement(query));
        pstmt->setString(1, nome_popular);

        try {
            pstmt->execute();
        } catch (sql::SQLException &e) {
            cerr << "Erro ao inserir nome popular: " << e.what() << endl;
            return;
        }
    }

    // Inserir sintomas
    cout << "Quantos sintomas deseja inserir? ";
    cin >> n_sintomas;
    cin.ignore();

    for (int i = 0; i < n_sintomas; i++) {
        int id_sintoma;

        cout << "Digite o ID do sintoma (consulte a tabela sintomas): ";
        cin >> id_sintoma;

        cout << "Digite o nível de ocorrência (Muito comum, Comum, Pouco comum, Raro, Muito raro): ";
        cin.ignore();
        getline(cin, nivel_ocorrencia);

         // Converter toda a string para minúsculas 
        transform(nivel_ocorrencia.begin(), nivel_ocorrencia.end(), nivel_ocorrencia.begin(), ::tolower); 
 
        // Converter a primeira letra para maiúscula 
        if (!nivel_ocorrencia.empty()) { 
            nivel_ocorrencia[0] = toupper(nivel_ocorrencia[0]); 
        } 

        // LAST_INSERT_ID -> para autoincremento
        query = "INSERT INTO doenca_sintoma (id_doenca, id_sintoma, nivel_ocorrencia) VALUES (LAST_INSERT_ID(), ?, ?)";
        pstmt.reset(connection->prepareStatement(query));
        pstmt->setInt(1, id_sintoma);
        pstmt->setString(2, nivel_ocorrencia);

        try {
            pstmt->execute();
        } catch (sql::SQLException &e) {
            cerr << "Erro ao inserir sintoma: " << e.what() << endl;
            return;
        }
    }

    cout << "Doença cadastrada com sucesso!\n";
}

#endif