// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
//         NÍVEL NOVATO: Cadastro Inicial dos Territórios
// ============================================================================
//
// OBJETIVOS DO NÍVEL NOVATO:
// - Criar uma struct chamada Territorio
// - Usar um vetor estático de 5 elementos para armazenar os territórios
// - Cadastrar os dados de cada território: Nome, Cor do Exército, Número de Tropas
// - Exibir o estado atual do mapa
//
// ============================================================================

#include <stdio.h>
#include <string.h>
#include <locale.h>

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
void cadastrarTerritorios(Territorio territorios[], int quantidade);
void exibirMapa(const Territorio territorios[], int quantidade);
void limparBufferEntrada();

// --- Função Principal (main) ---
int main() {
    // Configura o locale para português
    setlocale(LC_ALL, "Portuguese");
    
    // Declaração do vetor estático de territórios
    Territorio mapa[NUM_TERRITORIOS];
    
    // Exibe cabeçalho do programa
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║       🗺️  DESAFIO WAR ESTRUTURADO - NÍVEL NOVATO 🗺️          ║\n");
    printf("║              Cadastro Inicial dos Territórios                  ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    
    // Cadastra os dados dos territórios
    cadastrarTerritorios(mapa, NUM_TERRITORIOS);
    
    // Exibe o mapa completo
    exibirMapa(mapa, NUM_TERRITORIOS);
    
    return 0;
}

// --- Implementação das Funções ---

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
 * limparBufferEntrada()
 * Limpa o buffer de entrada (stdin) para evitar problemas com leituras
 * consecutivas de scanf e fgets.
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
