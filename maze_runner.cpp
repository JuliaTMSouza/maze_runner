#include <stdio.h>
#include <stack>
#include <iostream>

// Matriz de char representnado o labirinto
char **maze; // Voce também pode representar o labirinto como um vetor de vetores de char (vector<vector<char>>)

// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;

// Representação de uma posição
struct pos_t
{
	int i;
	int j;
};

// Estrutura de dados contendo as próximas
// posicões a serem exploradas no labirinto
std::stack<pos_t> valid_positions;
/* Inserir elemento:

	 pos_t pos;
	 pos.i = 1;
	 pos.j = 3;
	 valid_positions.push(pos)
 */
// Retornar o numero de elementos:
//    valid_positions.size();
//
// Retornar o elemento no topo:
//  valid_positions.top();
//
// Remover o primeiro elemento do vetor:
//    valid_positions.pop();

// Função que le o labirinto de um arquivo texto, carrega em
// memória e retorna a posição inicial
pos_t load_maze(const char *file_name)
{
	pos_t initial_pos;
	FILE *file_maze = fopen(file_name, "r");
	// Abre o arquivo para leitura (fopen)

	fscanf(file_maze, "%d %d\n", &num_rows, &num_cols);
	// Le o numero de linhas e colunas (fscanf)
	// e salva em num_rows e num_cols

	maze = (char **)malloc(num_rows * sizeof(char *));
	// Aloca a matriz maze (malloc)
	for (int i = 0; i < num_rows; ++i)
		maze[i] = (char *)malloc(num_cols * sizeof(char));
	// Aloca cada linha da matriz
	char barran;

	for (int i = 0; i < num_rows; ++i)
	{

		for (int j = 0; j < num_cols; ++j)
		{
			fscanf(file_maze, "%c", &maze[i][j]);

			if (maze[i][j] == 'e')
			{
				initial_pos.i = i;
				initial_pos.j = j;
			}
			// Le o valor da linha i+1,j do arquivo e salva na posição maze[i][j]
			// Se o valor for 'e' salvar o valor em initial_pos
		}
		barran = fscanf(file_maze, "%c", &barran);
	}
	return initial_pos;
}

// Função que imprime o labirinto
void print_maze()
{
	for (int i = 0; i < num_rows; ++i)
	{
		for (int j = 0; j < num_cols; ++j)
		{
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
}

// Função responsável pela navegação.
// Recebe como entrada a posição initial e retorna um booleando indicando se a saída foi encontrada
bool walk(pos_t pos)
{
	pos_t current_pos;
	current_pos.j = pos.j;
	current_pos.i = pos.i;
	int finalizado = 0;

	while (finalizado < 1)
	{
		int i = current_pos.i;
		int j = current_pos.j;
		std::cout << "i j" << i << j << std::endl;
		// std::cout << "hello" << std::endl;
		if (j + 1 < num_cols && (maze[i][j + 1] == 'x' || maze[i][j + 1] == 's'))
		{
			std::cout << "j+ " << maze[i][j + 1] << std::endl;
			pos_t valid_pos;
			valid_pos.i = i;
			valid_pos.j = j + 1;
			maze[i][j + 1] == '.';
			valid_positions.push(valid_pos);
		}
		std::cout << "Hello" << std::endl;
		if (j - 1 > -1 && (maze[i][j - 1] == 'x' || maze[i][j - 1] == 's'))
		{
			std::cout << "j- " << maze[i][j - 1] << std::endl;
			pos_t valid_pos;
			valid_pos.i = i;
			valid_pos.j = j - 1;
			maze[i][j - 1] == '.';
			valid_positions.push(valid_pos);
		}
		std::cout << "Hello2" << std::endl;
		if (i + 1 < num_rows  && (maze[i + 1][j] == 'x' || maze[i + 1][j] == 's'))
		{
			std::cout << "i+ " << maze[i + 1][j] << std::endl;
			pos_t valid_pos;
			valid_pos.i = i + 1;
			valid_pos.j = j;
			maze[i + 1][j] == '.';
			valid_positions.push(valid_pos);
		}
		std::cout << "Hello3" << std::endl;
		if ( i - 1 > -1 && (maze[i - 1][j] == 'x' || maze[i - 1][j] == 's'))
		{
			std::cout << "i-1 " << i-1 << " j " << j << " valor " << maze[i - 1][j] << std::endl;
			pos_t valid_pos;
			valid_pos.i = i - 1;
			valid_pos.j = j;
			maze[i - 1][j] == '.';
			valid_positions.push(valid_pos);
		}

		std::cout << "Tamanho valid " << valid_positions.size() << std::endl;

		current_pos.i = valid_positions.top().i;
		current_pos.j = valid_positions.top().j;
		if (maze[current_pos.i][current_pos.j] == 's') {
			finalizado += 1;
			return true;
		} 
		maze[current_pos.i][current_pos.j] = '.';
		std::cout << "i j valor" << current_pos.i << current_pos.j << maze[current_pos.i][current_pos.j] << std::endl;

		valid_positions.pop();

	}
	// Repita até que a saída seja encontrada ou não existam mais posições não exploradas
	// Marcar a posição atual com o símbolo '.'
	// Limpa a tela
	// Imprime o labirinto

	/* Dado a posição atual, verifica quais sao as próximas posições válidas
		Checar se as posições abaixo são validas (i>0, i<num_rows, j>0, j <num_cols)
		e se são posições ainda não visitadas (ou seja, caracter 'x') e inserir
		cada uma delas no vetor valid_positions
			- pos.i, pos.j+1
			- pos.i, pos.j-1
			- pos.i+1, pos.j
			- pos.i-1, pos.j
		Caso alguma das posiçÕes validas seja igual a 's', retornar verdadeiro
	*/

	// Verifica se a pilha de posições nao esta vazia
	// Caso não esteja, pegar o primeiro valor de  valid_positions, remove-lo e chamar a funçao walk com esse valor
	// Caso contrario, retornar falso
	if (!valid_positions.empty())
	{
		pos_t next_position = valid_positions.top();
		valid_positions.pop();
	}
	return false;
}

int main(int argc, char *argv[])
{
	// carregar o labirinto com o nome do arquivo recebido como argumento
	pos_t initial_pos = load_maze("../data/maze3.txt");
	std::cout << "Posição inicial i:  " << initial_pos.i << " j: " << initial_pos.j << std::endl;
	// chamar a função de navegação
	bool exit_found = walk(initial_pos);

	// Tratar o retorno (imprimir mensagem)
	print_maze();
	return 0;
}
