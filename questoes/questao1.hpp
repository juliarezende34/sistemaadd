#ifndef QUESTAO1_HPP
#define QUESTAO1_HPP
#include "../include.hpp"

void cadastrarPatogeno(unique_ptr<sql::Connection> &connection) {

    string nome, tipo;
    int id_patogeno;

    cout << "Digite o nome do patógeno: ";
    cin >> nome;

    cout << "Digite o tipo do patógeno: ";
    cin >> tipo;

    cout << "Digite o id do patógeno: ";
    cin >> id_patogeno;

    string query = "INSERT INTO patogenos (id, nome_cientifico, tipo) VALUES (?, ?, ?)";
    unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));
    pstmt->setInt(1, id_patogeno);
    pstmt->setString(2, nome);
    pstmt->setString(3, tipo);

    try {
        pstmt->execute();
        cout << "Patógeno inserido com sucesso!\n";
    }
    catch (sql::SQLException &e) {
        cerr << "Erro ao inserir patógeno: " << e.what() << endl;
        return;
    }


}

void cadastrarDoencaSintoma(unique_ptr<sql::Connection> &connection, int id_sintoma, string id_doenca) {

    string nivel_ocorrencia;

    cout << "Digite o nível de ocorrência (Muito comum, Comum, Pouco comum, Raro, Muito raro): ";
    getline(cin, nivel_ocorrencia);

    // Converter toda a string para minúsculas 
    // transform(nivel_ocorrencia.begin(), nivel_ocorrencia.end(), nivel_ocorrencia.begin(), ::tolower);

    // // Converter a primeira letra para maiúscula 
    // if (!nivel_ocorrencia.empty()) {
    //     nivel_ocorrencia[0] = toupper(nivel_ocorrencia[0]);
    // }

    string query2 = "INSERT INTO doenca_sintoma (id_doenca, id_sintoma, nivel_ocorrencia) VALUES (?, ?, ?)";
    unique_ptr<sql::PreparedStatement> pstmt2(connection->prepareStatement(query2));

    pstmt2->setString(1, id_doenca);
    pstmt2->setInt(2, id_sintoma);
    pstmt2->setString(3, nivel_ocorrencia);

    try {
        pstmt2->execute();
    }
    catch (sql::SQLException &e) {
        cerr << "Erro ao inserir doenca_sintoma: " << e.what() << endl;
        return;
    }
}

void cadastrarSintoma(unique_ptr<sql::Connection> &connection, string id_doenca) {

    int opcao = 0;
    cout << "\nDeseja inserir algum sintoma?\n[1]Sim\n[0]Não\n";
    cin >> opcao;

    int id_sintoma = 0;
    int n_sintomas;
    string nome;

    if (opcao) {

        cout << "Quantos sintomas deseja inserir? ";
        cin >> n_sintomas;
        cin.ignore();

        for (int i = 0; i < n_sintomas; i++) {
            id_sintoma = 0;
            bool novo_sintoma;

            cout << "\nÉ um sintoma novo? \nSim[1]\nNão[0]\n";
            cin >> novo_sintoma;

            if (novo_sintoma) {
                cout << "Digite o ID do sintoma: ";
                cin >> id_sintoma;
                cin.ignore();

                cout << "Digite o nome do sintoma: ";
                getline(cin, nome);
                cin.ignore();

                // Inserir o novo sintoma na tabela sintoma
                string query = "INSERT INTO sintomas (id, nome) VALUES (?, ?)";
                unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));
                pstmt->setInt(1, id_sintoma);
                pstmt->setString(2, nome);

                try {
                    pstmt->execute();
                }
                catch (sql::SQLException &e) {
                    cerr << "Erro ao inserir sintoma: " << e.what() << endl;
                    return;
                }
            }
        }
    } else {
        cout << "Digite o ID do sintoma (consulte a tabela sintomas): ";
        cin >> id_sintoma;
        cin.ignore();

        // Buscar o nome do sintoma a partir do ID
        string query = "SELECT nome FROM sintomas WHERE id = ?";
        unique_ptr<sql::PreparedStatement> pstmt2(connection->prepareStatement(query));
        pstmt2->setInt(1, id_sintoma);

        unique_ptr<sql::ResultSet> res(pstmt2->executeQuery());

        if (res->next()) {} else {
            cerr << "Sintoma com ID " << id_sintoma << " não encontrado." << endl;
            return;
        }
    }

    cadastrarDoencaSintoma(connection, id_sintoma, id_doenca);

}

void cadastrarNomePopular(unique_ptr<sql::Connection> &connection) {

    int opcao = 0;
    int n_nomes_populares;
    string nome, id_doenca;

    cout << "\nDeseja cadastrar um nome popular?\n[1]Sim\n[0]Não\n";
    cin >> opcao;

    if (opcao) {

        cout << "Quantos nomes populares deseja inserir? ";
        cin >> n_nomes_populares;
        cin.ignore();  // Limpa o buffer de entrada após cin >> n_nomes_populares

        cout << "Digite o CID da doenca: ";
        getline(cin, id_doenca);  // Captura o CID da doença

        for (int i = 0; i < n_nomes_populares; i++) {
            cout << "Digite o nome popular: ";
            getline(cin, nome);  // Captura o nome popular

            // Inserir o nome popular na tabela nome_popular
            string query = "INSERT INTO nome_popular (id_doenca, nome) VALUES (?, ?)";
            unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));

            pstmt->setString(1, id_doenca);  // Define o CID da doença
            pstmt->setString(2, nome);  // Define o nome popular

            try {
                pstmt->execute();
                cout << "Nome popular inserido com sucesso!\n";
            }
            catch (sql::SQLException &e) {
                cerr << "Erro ao inserir nome popular: " << e.what() << endl;
                return;
            }
        }

    }

    cadastrarSintoma(connection, id_doenca);  // Passa o CID para a próxima função
}

void cadastrarDoenca(unique_ptr<sql::Connection> &connection) {

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
    }
    catch (sql::SQLException &e) {
        cerr << "Erro ao inserir doença: " << e.what() << endl;
        return;
    }
}

#endif