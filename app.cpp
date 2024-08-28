#include "include.hpp"
#include "questoes/questao2.hpp"
#include "questoes/questao3.hpp"

using namespace std;

int main(){
    int op = -1, opConsulta = -1; 
    string cid;  

    try {

        // Configuração da conexão com o banco de dados
        
        while(op != 0){
            //sql::SQLString url("jdbc:mariadb://127.0.0.1:3306/sistemaadd");
            //sql::Properties properties({{"user", "root"}, {"password", "123"}});

            // Cria a conexão com o banco de dados
            sql::Driver* driver = sql::mariadb::get_driver_instance();
            unique_ptr<sql::Connection> connection(driver->connect(url, properties)); 

            cout << string(150, '-') << endl;
            cout << "\nInsira o número da operação desejada:\n[0] Sair\n[1] Gerenciamento de Dados\n[2] Consulta ao Catálogo de Doenças\n";
            cout << "[3] Apoio ao Diagnóstico\n[4] Emissão de Relatórios\n[5] Logs de acesso e operações\n>";
            cin >> op;

            switch(op){
                case 0:
                    cout << "\nObrigada por utilizar nosso sistema!\n";
                break;

                case 1:
                break;

                case 2:
                    imprimirDoencas(connection);
                    cout << "\nDeseja realizar uma pesquisa detalhada?\n[1] Sim\n[0] Não\n>";
                    cin >> opConsulta;
                    if(opConsulta == 1){
                        consultaEspecifica(connection);
                    }
                    else if (opConsulta == 0){
                        cout << "Retornando ao menu principal!\n";
                    }
                    else{
                        cout << "Opção inválida!\n";
                    }
                break;

                case 3:
                    consultaDoencasComSintomas(connection);
                break;

                case 4:
                break;

                case 5:
                break;

                default:
                break;
            }
            // Encerra a conexão
            connection->close();
        }

        

    } catch (sql::SQLException& e) {
        cerr << "Erro ao conectar/acessar o banco de dados: " << e.what() << endl;
        return EXIT_FAILURE;
    } catch (...) {
        cerr << "Erro inesperado!" << endl;
        return EXIT_FAILURE;
    }
    return 0;
}