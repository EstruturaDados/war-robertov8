// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
//         NÍVEL AVENTUREIRO: Batalhas Estratégicas
// ============================================================================
//
// OBJETIVOS DO NÍVEL AVENTUREIRO:
// - Substituir vetor estático por alocação dinâmica com calloc
// - Criar função para simular ataques entre dois territórios
// - Utilizar números aleatórios para representar dados de batalha
// - Implementar laço interativo para batalhas
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
Territorio* alocarMapa(int quantidade);
void cadastrarTerritorios(Territorio territorios[], int quantidade);
void exibirMapa(const Territorio territorios[], int quantidade);
void exibirMenuPrincipal();
void faseDeAtaque(Territorio territorios[], int quantidade);
void simularAtaque(Territorio territorios[], int atacante, int defensor);
void liberarMemoria(Territorio *territorios);
void limparBufferEntrada();

// --- Função Principal (main) ---
int main() {
    // Configura o locale para português
    setlocale(LC_ALL, "Portuguese");
    
    // Inicializa a semente para números aleatórios
    srand(time(NULL));
    
    // Aloca dinamicamente a memória para os territórios
    Territorio *mapa = alocarMapa(NUM_TERRITORIOS);
    if (mapa == NULL) {
        printf("❌ Erro ao alocar memória para o mapa!\n");
        return 1;
    }
    
    // Exibe cabeçalho do programa
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║      🗺️  DESAFIO WAR ESTRUTURADO - NÍVEL AVENTUREIRO 🗺️      ║\n");
    printf("║                   Batalhas Estratégicas                        ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    // Cadastra os dados dos territórios
    cadastrarTerritorios(mapa, NUM_TERRITORIOS);
    
    // Laço principal do jogo
    int opcao;
    do {
        // Exibe o mapa atual
        exibirMapa(mapa, NUM_TERRITORIOS);
        
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
            case 0:
                printf("🏳️  Encerrando o jogo. Até a próxima batalha!\n");
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
    
    // Libera a memória alocada
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
 * cadastrarTerritorios()
 * Solicita ao usuário os dados de cada território e preenche o vetor.
 * Parâmetros:
 *   - territorios[]: vetor de territórios a ser preenchido (passado por referência)
 *   - quantidade: número de territórios a cadastrar
 */
void cadastrarTerritorios(Territorio territorios[], int quantidade) {
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("           CADASTRO DE TERRITÓRIOS (%d territórios)\n", quantidade);
    printf("═══════════════════════════════════════════════════════════════\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("▶ Território %d de %d:\n", i + 1, quantidade);
        printf("─────────────────────────────────\n");
        
        // Lê o nome do território
        printf("  Nome do território: ");
        fgets(territorios[i].nome, TAM_STRING, stdin);
        // Remove o '\n' do final da string
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        
        // Lê a cor do exército
        printf("  Cor do exército: ");
        fgets(territorios[i].corExercito, TAM_STRING, stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';
        
        // Lê o número de tropas
        printf("  Número de tropas: ");
        scanf("%d", &territorios[i].numTropas);
        limparBufferEntrada();
        
        printf("\n");
    }
    
    printf("✓ Todos os territórios foram cadastrados com sucesso!\n\n");
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
    printf("║  [0] 🏳️  Sair do Jogo                                          ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
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
 * limparBufferEntrada()
 * Limpa o buffer de entrada (stdin) para evitar problemas com leituras
 * consecutivas de scanf e fgets.
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
