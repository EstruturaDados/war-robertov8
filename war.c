// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
//         NÍVEL MESTRE: Missões e Modularização Total
// ============================================================================
//
// OBJETIVOS DO NÍVEL MESTRE:
// - Dividir o código em funções bem definidas (modularização total)
// - Implementar um sistema de missões aleatórias
// - Verificar cumprimento da missão
// - Aplicar boas práticas (uso de const, passagem por referência, etc.)
// - Inicialização automática dos territórios
//
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

// --- Constantes Globais ---
#define NUM_TERRITORIOS 5
#define TAM_STRING 50

// --- Estrutura de Dados ---
typedef struct {
    char nome[TAM_STRING];
    char corExercito[TAM_STRING];
    int numTropas;
} Territorio;

// --- Protótipos das Funções ---
// Funções de setup e gerenciamento de memória:
Territorio* alocarMapa(int quantidade);
void inicializarTerritorios(Territorio territorios[], int quantidade);
void liberarMemoria(Territorio *territorios);

// Funções de interface com o usuário:
void exibirMenuPrincipal();
void exibirMapa(const Territorio territorios[], int quantidade);
void exibirMissao(int idMissao);

// Funções de lógica principal do jogo:
void faseDeAtaque(Territorio territorios[], int quantidade);
void simularAtaque(Territorio territorios[], int atacante, int defensor);
int sortearMissao();
int verificarVitoria(const Territorio territorios[], int quantidade, int idMissao, const char *corJogador);

// Função utilitária:
void limparBufferEntrada();

// --- Função Principal (main) ---
int main() {
    // 1. Configuração Inicial (Setup)
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    
    // Aloca dinamicamente a memória para os territórios
    Territorio *mapa = alocarMapa(NUM_TERRITORIOS);
    if (mapa == NULL) {
        printf("❌ Erro ao alocar memória para o mapa!\n");
        return 1;
    }
    
    // Exibe cabeçalho do programa
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║        🗺️  DESAFIO WAR ESTRUTURADO - NÍVEL MESTRE 🗺️         ║\n");
    printf("║              Missões e Modularização Total                     ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    // Inicializa os territórios automaticamente
    inicializarTerritorios(mapa, NUM_TERRITORIOS);
    
    // Define a cor do jogador
    char corJogador[TAM_STRING] = "Azul";
    printf("🎮 Você está jogando com o exército: %s\n\n", corJogador);
    
    // Sorteia a missão secreta do jogador
    int missao = sortearMissao();
    printf("📜 Sua missão foi definida!\n");
    printf("   Use a opção [2] no menu para visualizar sua missão.\n\n");
    
    printf("⏸️  Pressione ENTER para iniciar o jogo...");
    getchar();
    printf("\n");
    
    // 2. Laço Principal do Jogo (Game Loop)
    int opcao;
    int venceu = 0;
    
    do {
        // Exibe o mapa atual
        exibirMapa(mapa, NUM_TERRITORIOS);
        
        // Exibe a missão atual
        printf("\n");
        exibirMissao(missao);
        
        // Exibe o menu de opções
        exibirMenuPrincipal();
        
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();
        printf("\n");
        
        switch (opcao) {
            case 1:
                faseDeAtaque(mapa, NUM_TERRITORIOS);
                break;
                
            case 2:
                // Verifica se o jogador cumpriu a missão
                if (verificarVitoria(mapa, NUM_TERRITORIOS, missao, corJogador)) {
                    printf("╔════════════════════════════════════════════════════════════════╗\n");
                    printf("║                    🎉 VITÓRIA! 🎉                              ║\n");
                    printf("╠════════════════════════════════════════════════════════════════╣\n");
                    printf("║  Parabéns! Você completou sua missão com sucesso!             ║\n");
                    printf("║  O exército %s dominou o mundo!                         ║\n", corJogador);
                    printf("╚════════════════════════════════════════════════════════════════╝\n");
                    venceu = 1;
                    opcao = 0; // Encerra o jogo
                } else {
                    printf("╔════════════════════════════════════════════════════════════════╗\n");
                    printf("║                  MISSÃO AINDA NÃO CUMPRIDA                     ║\n");
                    printf("╠════════════════════════════════════════════════════════════════╣\n");
                    printf("║  Continue lutando para completar sua missão!                  ║\n");
                    printf("╚════════════════════════════════════════════════════════════════╝\n");
                }
                break;
                
            case 0:
                if (!venceu) {
                    printf("🏳️  Encerrando o jogo. Até a próxima batalha!\n");
                }
                break;
                
            default:
                printf("❌ Opção inválida! Tente novamente.\n");
        }
        
        if (opcao != 0) {
            printf("\n⏸️  Pressione ENTER para continuar...");
            getchar();
            printf("\n");
        }
        
    } while (opcao != 0);
    
    // 3. Limpeza
    liberarMemoria(mapa);
    
    return 0;
}

// --- Implementação das Funções ---

/**
 * alocarMapa()
 * Aloca dinamicamente a memória para o vetor de territórios usando calloc.
 * Parâmetros:
 *   - quantidade: número de territórios a alocar
 * Retorna:
 *   - Ponteiro para a memória alocada ou NULL em caso de falha
 */
Territorio* alocarMapa(int quantidade) {
    Territorio *mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));
    return mapa;
}

/**
 * inicializarTerritorios()
 * Preenche os dados iniciais de cada território no mapa automaticamente.
 * Esta função modifica o mapa passado por referência (ponteiro).
 * Parâmetros:
 *   - territorios[]: vetor de territórios a ser preenchido
 *   - quantidade: número de territórios a inicializar
 */
void inicializarTerritorios(Territorio territorios[], int quantidade) {
    // Dados predefinidos dos territórios
    const char* nomes[] = {"Brasil", "Argentina", "Peru", "Colômbia", "Chile"};
    const char* cores[] = {"Azul", "Verde", "Vermelho", "Verde", "Amarelo"};
    const int tropas[] = {5, 3, 4, 2, 3};
    
    for (int i = 0; i < quantidade && i < 5; i++) {
        strcpy(territorios[i].nome, nomes[i]);
        strcpy(territorios[i].corExercito, cores[i]);
        territorios[i].numTropas = tropas[i];
    }
    
    printf("✓ Territórios inicializados com sucesso!\n\n");
}

/**
 * exibirMapa()
 * Exibe o estado atual de todos os territórios formatado como uma tabela.
 * Parâmetros:
 *   - territorios[]: vetor de territórios a ser exibido (const - apenas leitura)
 *   - quantidade: número de territórios no vetor
 */
void exibirMapa(const Territorio territorios[], int quantidade) {
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                    🗺️  MAPA DOS TERRITÓRIOS 🗺️                ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    printf("┌────┬────────────────────────┬────────────────────────┬─────────┐\n");
    printf("│ Nº │      TERRITÓRIO        │    COR DO EXÉRCITO     │ TROPAS  │\n");
    printf("├────┼────────────────────────┼────────────────────────┼─────────┤\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("│ %2d │ %-22s │ %-22s │  %5d  │\n",
               i + 1,
               territorios[i].nome,
               territorios[i].corExercito,
               territorios[i].numTropas);
    }
    
    printf("└────┴────────────────────────┴────────────────────────┴─────────┘\n");
}

/**
 * exibirMenuPrincipal()
 * Exibe o menu de opções disponíveis para o jogador.
 */
void exibirMenuPrincipal() {
    printf("\n╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                        MENU PRINCIPAL                          ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║  [1] ⚔️  Fase de Ataque                                        ║\n");
    printf("║  [2] 🎯 Verificar Missão                                       ║\n");
    printf("║  [0] 🏳️  Sair do Jogo                                          ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
}

/**
 * exibirMissao()
 * Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.
 * Parâmetros:
 *   - idMissao: identificador da missão (1 ou 2)
 */
void exibirMissao(int idMissao) {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│                      📜 MISSÃO SECRETA 📜                       │\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");
    
    if (idMissao == 1) {
        printf("│  🎯 Objetivo: Destruir o exército VERDE                        │\n");
        printf("│     → Todos os territórios verdes devem ser conquistados.     │\n");
    } else if (idMissao == 2) {
        printf("│  🎯 Objetivo: Conquistar 3 TERRITÓRIOS                         │\n");
        printf("│     → Domine pelo menos 3 territórios com seu exército.       │\n");
    } else {
        printf("│  ⚠️  Missão desconhecida!                                      │\n");
    }
    
    printf("└────────────────────────────────────────────────────────────────┘\n");
}

/**
 * faseDeAtaque()
 * Gerencia a interface para a ação de ataque.
 * Solicita ao jogador os territórios de origem e destino do ataque.
 * Parâmetros:
 *   - territorios[]: vetor de territórios
 *   - quantidade: número de territórios no vetor
 */
void faseDeAtaque(Territorio territorios[], int quantidade) {
    int atacante, defensor;
    
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                    ⚔️  FASE DE ATAQUE ⚔️                       ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    printf("Escolha o território ATACANTE (1 a %d): ", quantidade);
    scanf("%d", &atacante);
    limparBufferEntrada();
    
    printf("Escolha o território DEFENSOR (1 a %d): ", quantidade);
    scanf("%d", &defensor);
    limparBufferEntrada();
    
    // Validações básicas
    if (atacante < 1 || atacante > quantidade || defensor < 1 || defensor > quantidade) {
        printf("\n❌ Território inválido! Os territórios devem estar entre 1 e %d.\n", quantidade);
        return;
    }
    
    if (atacante == defensor) {
        printf("\n❌ Um território não pode atacar a si mesmo!\n");
        return;
    }
    
    // Ajusta os índices (de 1-based para 0-based)
    simularAtaque(territorios, atacante - 1, defensor - 1);
}

/**
 * simularAtaque()
 * Executa a lógica de uma batalha entre dois territórios.
 * Realiza validações, simula lançamento de dados e atualiza o número de tropas.
 * Se um território for conquistado, atualiza seu dono.
 * Parâmetros:
 *   - territorios[]: vetor de territórios
 *   - atacante: índice do território atacante
 *   - defensor: índice do território defensor
 */
void simularAtaque(Territorio territorios[], int atacante, int defensor) {
    printf("\n════════════════════════════════════════════════════════════════\n");
    printf("                      🎲 SIMULAÇÃO DE BATALHA 🎲\n");
    printf("════════════════════════════════════════════════════════════════\n\n");
    
    // Exibe informações dos territórios
    printf("⚔️  ATACANTE: %s (%s) - %d tropas\n", 
           territorios[atacante].nome,
           territorios[atacante].corExercito,
           territorios[atacante].numTropas);
    
    printf("🛡️  DEFENSOR: %s (%s) - %d tropas\n\n",
           territorios[defensor].nome,
           territorios[defensor].corExercito,
           territorios[defensor].numTropas);
    
    // Validação: atacante precisa ter pelo menos 2 tropas (1 fica no território)
    if (territorios[atacante].numTropas < 2) {
        printf("❌ O território atacante precisa ter pelo menos 2 tropas para atacar!\n");
        printf("   (uma tropa deve sempre permanecer no território)\n");
        return;
    }
    
    // Validação: não pode atacar território da mesma cor
    if (strcmp(territorios[atacante].corExercito, territorios[defensor].corExercito) == 0) {
        printf("❌ Você não pode atacar um território da mesma cor!\n");
        return;
    }
    
    // Simula lançamento dos dados
    int dadoAtacante = (rand() % 6) + 1;  // Dado de 1 a 6
    int dadoDefensor = (rand() % 6) + 1;  // Dado de 1 a 6
    
    printf("🎲 Lançando os dados...\n\n");
    printf("   Dado do ATACANTE: 🎲 %d\n", dadoAtacante);
    printf("   Dado do DEFENSOR: 🎲 %d\n\n", dadoDefensor);
    
    // Determina o vencedor da batalha
    if (dadoAtacante > dadoDefensor) {
        printf("✅ O ATACANTE venceu a batalha!\n");
        territorios[defensor].numTropas--;
        printf("   → O defensor perdeu 1 tropa. Tropas restantes: %d\n", 
               territorios[defensor].numTropas);
        
        // Verifica se o território foi conquistado
        if (territorios[defensor].numTropas == 0) {
            printf("\n🏴 TERRITÓRIO CONQUISTADO!\n");
            printf("   %s agora pertence ao exército %s!\n",
                   territorios[defensor].nome,
                   territorios[atacante].corExercito);
            
            // Atualiza a cor do exército e move uma tropa
            strcpy(territorios[defensor].corExercito, territorios[atacante].corExercito);
            territorios[defensor].numTropas = 1;
            territorios[atacante].numTropas--;
        }
    } else {
        printf("✅ O DEFENSOR resistiu ao ataque!\n");
        printf("   → Nenhuma tropa foi perdida.\n");
        printf("   (Empates e vitórias do defensor favorecem a defesa)\n");
    }
    
    printf("\n════════════════════════════════════════════════════════════════\n");
}

/**
 * liberarMemoria()
 * Libera a memória previamente alocada para o mapa usando free.
 * Parâmetros:
 *   - territorios: ponteiro para a memória a ser liberada
 */
void liberarMemoria(Territorio *territorios) {
    free(territorios);
}

/**
 * sortearMissao()
 * Sorteia e retorna um ID de missão aleatório para o jogador.
 * Retorna:
 *   - 1: Destruir o exército Verde
 *   - 2: Conquistar 3 territórios
 */
int sortearMissao() {
    return (rand() % 2) + 1;  // Retorna 1 ou 2
}

/**
 * verificarVitoria()
 * Verifica se o jogador cumpriu os requisitos de sua missão atual.
 * Implementa a lógica para cada tipo de missão.
 * Parâmetros:
 *   - territorios[]: vetor de territórios (const - apenas leitura)
 *   - quantidade: número de territórios
 *   - idMissao: identificador da missão (1 ou 2)
 *   - corJogador: cor do exército do jogador
 * Retorna:
 *   - 1 (verdadeiro) se a missão foi cumprida
 *   - 0 (falso) caso contrário
 */
int verificarVitoria(const Territorio territorios[], int quantidade, int idMissao, const char *corJogador) {
    if (idMissao == 1) {
        // Missão 1: Destruir o exército Verde
        // Verifica se não existe nenhum território verde
        int existeVerde = 0;
        for (int i = 0; i < quantidade; i++) {
            if (strcmp(territorios[i].corExercito, "Verde") == 0) {
                existeVerde = 1;
                break;
            }
        }
        return !existeVerde;  // Retorna 1 se NÃO existir verde (missão cumprida)
        
    } else if (idMissao == 2) {
        // Missão 2: Conquistar 3 territórios
        // Conta quantos territórios pertencem ao jogador
        int territoriosDoJogador = 0;
        for (int i = 0; i < quantidade; i++) {
            if (strcmp(territorios[i].corExercito, corJogador) == 0) {
                territoriosDoJogador++;
            }
        }
        return territoriosDoJogador >= 3;  // Retorna 1 se tiver 3 ou mais territórios
    }
    
    return 0;  // Missão desconhecida ou não cumprida
}

/**
 * limparBufferEntrada()
 * Limpa o buffer de entrada (stdin) para evitar problemas com leituras
 * consecutivas de scanf e fgets.
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
