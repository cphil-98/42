#include <unistd.h>
#include <stdlib.h>

int	error(void);
char	*check_input(char *input);
char	*strip(char *input, char c);
int	dim_(char *input);
char	*matrice_(int dim, char *input);
int	*inizializza_arr_int(int size, int c);

void	print_(char *matrice, int dim);
int	inserisci_combs(char *matrice, int dim);
int	inserisci_col(char *matrice, int dim, int index);
int	inserisci_row(char *matrice, int dim, int index);
int	fattoriale(int n);
int	inserisci_perm(char *mancanti, char *matrice, int index, int incremento, int dim, int *sovrascritti);
void	ripristina_(int *sovrascritti, char *matrice);
void	perm_(char *mancanti, int *dir, int size);
void	print_row(char *matrice, int index, int dim);
int	inserisci_combn(char *matrice, int dim, int index);
int	inserisci_comb1(char *matrice, int dim, int index);
int	inserisci_comb2(char *matrice, int dim, int index);
int	respective_start(int index, int dim);
int	respective_increment(int index, int dim);
int	inserisci(char *matrice, int index, char input, int dim);
int	manca_(char *mancanti, int i, int counter);
int	check_cell(char *matrice, int index, char input, int dim);
int	full_(char *matrice, int dim);
void	trova_mancanti(char *mancanti, char *matrice, int dim, int index, int incremento);
char	*inizializza_mancanti(char *matrice, int dim, int index, int incremento);
int	mancanti_quanti_sono(char *matrice, int dim, int index, int incremento);
int	check_opp(char *matrice, int start, int incremento, int dim);
int	check_opps(char *matrice, int index, int incremento, int dim);
int	respective_check(int start, int incremento, int dim);
char	mobile_(char *mancanti, int *dir, int size);
int	pos_(char *mancanti, int size, char mobile);
void	swap(char *mancanti, int pos1, int pos2);
int	manca_(char *mancanti, int i, int counter);
int	respective_opp(int start, int incremento, int dim);

int	main(int argc, char **argv)
{
	int	dim;
	char	*input;
	char	*matrice;

	if (argc != 2)
		return error();
	if (!(input = check_input(argv[1])))
		return error();
	if (!(dim = dim_(input)))
		return error();
	matrice = matrice_(dim, input);
	if (!inserisci_combs(matrice, dim))
		return error();
	if (!inserisci_col(matrice, dim, 0))
		return error();
	print_(matrice, dim);
	free(matrice);
	return (0);
}

char	*matrice_(int dim, char *input)
{
	char	*matrice;
	int	i;
	int	j;

	matrice = (char *) malloc(sizeof(char) * (dim + 4) * dim);
	i = -1;
	while (++i < dim * dim)
		matrice[i] = '0';
	j = 0;
	while (i < (dim + 4) * dim)
		matrice[i++] = input[j++];
	return (matrice);
}

char	*check_input(char *input)
{
	int	i;

	input = strip(input, ' ');
	i = -1;
	while (input[++i] != 0)
		if (input[i] < '0' || input[i] > '9')
			return (0);
	return (input);
}

char	*strip(char *input, char c)
{
	int	i;
	int	counter;
	int	len;
	char	*output;

	counter = 0;
	i = -1;
	while (input[++i] != 0)
		if (input[i] == c)
			counter++;
	len = i - counter;
	output = (char *) malloc(sizeof(char) * len);
	i = -1;
	while (++i < len)
		output[i] = input[2*i];
	return output;
}

int	dim_(char *input)
{
	int	dim;

	dim = -1;
	while (input[++dim] != 0) {}
	return (dim % 4 == 0 ? dim / 4 : 0);
}

int	error()
{
	write(1, "Error\n", 6);
	return 0;
}

void	print_(char *matrice, int dim)
{
	int	index;

	write(1, "\t", 1);
	print_row(matrice, dim, dim);
	write(1, "\n\n\n", 3);
	index = 0;
	while (index < dim)
	{
		write(1, &matrice[dim * (dim + 2) + index], 1);
		write(1, "\t", 1);
		print_row(matrice, index, dim);
		write(1, &matrice[dim * (dim + 2) + 4 + index], 1);
		write(1, "\n", 1);
		index++;
	}
	write(1, "\n\n\t", 3);
	print_row(matrice, dim + 1, dim);
	write(1, "\n\n", 2);
}

void	print_row(char *matrice, int index, int dim)
{
	int	start;
	int	counter;

	start = dim * index;
	counter = 0;
	while (counter < dim)
	{
		write(1, &matrice[start + counter], 1);
		write(1, "\t", 1);
		counter++;
	}
}

int	inserisci_combs(char *matrice, int dim)
{
	char	*cella;
	char	*opposta;
	int	i;

	i = -1;
	cella = &matrice[dim * dim];
	opposta = cella + dim;
	while (++i < 4*dim)
	{
		if ((*cella == '0' + dim) && (!inserisci_combn(matrice, dim, i)))
			return (0);
		else if ((*cella == '1') && (!inserisci_comb1(matrice, dim, i)))
			return (0);
		else if ((*cella == '2' && *opposta == '0' + dim - 1)
		&& (!inserisci_comb2(matrice, dim, i)))
			return (0);
		cella++;
		if ((i / 4) % 2 == 0)
			opposta = cella + dim;
		else
			opposta = cella - dim;
	}
	return (1);
}

int	inserisci_combn(char *matrice, int dim, int index)
{
	int	start;
	int	incremento;
	int	i;

	i = -1;
	start = respective_start(index, dim);
	incremento = respective_increment(index, dim);
	while (++i < dim)
	{
		if (matrice[start + incremento * i] == '0'
		&& !inserisci(matrice, start + incremento * i, '1' + i, dim))
			return 0;
		else if (matrice[start + incremento * i] != '1' + i)
			return 0;
	}
	return 1;
}

int	inserisci_comb1(char *matrice, int dim, int index)
{
	int	start;

	start = respective_start(index, dim);
	if (matrice[start] == '0')
		return (inserisci(matrice, start, '4', dim));
	return matrice[start] == '4';
}

int	inserisci_comb2(char *matrice, int dim, int index)
{
	int	start;
	int	incremento;

	start = respective_start(index, dim);
	incremento = respective_increment(index, dim);
	if (matrice[start + incremento] == '0')
		return (inserisci(matrice, start + incremento, '4', dim));
	return matrice[start + incremento] == '4';
}

int	respective_start(int index, int dim)
{
	int start = index % dim;

	if (index / dim == 0)
		return (start);
	else if (index / dim == 1)
		return (start + dim * (dim - 1));
	else if (index / dim == 2)
		return (start * dim);
	else
		return (start * dim + (dim - 1));
}

int	respective_increment(int index, int dim)
{
	if (index / dim == 0)
		return (dim);
	else if (index / dim == 1)
		return (-dim); 
	else if (index / dim == 2)
		return (1);
	else
		return (-1);
}

int	inserisci(char *matrice, int index, char input, int dim)
{
	matrice[index] = input;
	if (!check_cell(matrice, index, input, dim))
	{
		matrice[index] = '0';
		return (0);
	}
	return 1;
}

int	check_cell(char *matrice, int index, char input, int dim)
{
	int	row;
	int	i;
	int	counter;

	counter = 0;
	row = index / dim;
	index %= 4;
	i = -1;
	while (++i < dim)
		if (matrice[index + dim * i] == input)
			counter++;
	i = -1;
	while (++i < dim)
		if (matrice[row * dim + i] == input)
			counter++;
	return (counter == 2 ? 1 : 0);
}

int	inserisci_col(char *matrice, int dim, int index)
{
	char	*mancanti;
	int	*sovrascritti;
	int	*dir;
	int	i;

	if (full_(matrice, dim))
		return (1);
	mancanti = inizializza_mancanti(matrice, dim, index, 4);
	dir = inizializza_arr_int(mancanti[0], 0);
	i = fattoriale(mancanti[0]);
	while (--i >= 0)
	{
		sovrascritti = inizializza_arr_int(mancanti[0] + 1, -1);
		if (inserisci_perm(mancanti, matrice, index, 4, dim, sovrascritti)
		&& inserisci_row(matrice, dim, index))
			return (1);
		perm_(mancanti + 1, dir, mancanti[0]);
		ripristina_(sovrascritti, matrice);
		free(sovrascritti);
	}
	free(mancanti);
	free(dir);
	return (0);
}

int	inserisci_row(char *matrice, int dim, int index)
{
	char	*mancanti;
	int	*sovrascritti;
	int	*dir;
	int	i;

	if (full_(matrice, dim))
		return (1);
	mancanti = inizializza_mancanti(matrice, dim, index, 1);
	dir = inizializza_arr_int(mancanti[0], 0);
	i = fattoriale(mancanti[0]);
	while (--i >= 0)
	{
		sovrascritti = inizializza_arr_int(mancanti[0] + 1, -1);
		if (inserisci_perm(mancanti, matrice, index, 1, dim, sovrascritti)
		&& inserisci_col(matrice, dim, index+1))
			return (1);
		perm_(mancanti + 1, dir, mancanti[0]);
		ripristina_(sovrascritti, matrice);
		free(sovrascritti);
	}
	free(mancanti);
	free(dir);
	return (0);
}

int	*inizializza_arr_int(int size, int c)
{
	int	*output;
	int	i;

	output = (int *) malloc(sizeof(int) * size);
	output[0] = 0;
	i = 0;
	while (++i < size)
		output[i] = c;
	return output;
}

int	full_(char *matrice, int dim)
{
	int	index;
	
	index = -1;
	dim *= dim;
	while (++index < dim)
		if (matrice[index] == '0')
			return (0);
	return (1);
}

char	*inizializza_mancanti(char *matrice, int dim, int index, int incremento)
{
	char	*mancanti;
	int	counter;

	counter = mancanti_quanti_sono(matrice, dim, index, incremento);
	mancanti = (char *) malloc(sizeof(char) * (counter + 1));
	mancanti[0] = counter;
	trova_mancanti(mancanti, matrice, dim, index, incremento);
	return (mancanti);
}

int	fattoriale(int n)
{
	int	fattoriale;
	int	i;

	fattoriale = 1;
	i = 1;
	while (++i <= n)
		fattoriale *= i;
	return (fattoriale);
}

int	inserisci_perm(char *mancanti, char *matrice, int index, int incremento, int dim, int *sovrascritti)
{
	int	i;

	i = 0;
	if (incremento == 1)
		index *= 4;
	while (sovrascritti[0] < mancanti[0])
	{
		if (matrice[index + incremento * i] != '0')
			i++;
		else if (!inserisci(matrice, index + incremento * i, mancanti[sovrascritti[0] + 1], dim))
			break;
		else
			sovrascritti[++sovrascritti[0]] = index + incremento * i++;
	}
	if (sovrascritti[0] != mancanti[0] || !check_opps(matrice, index, incremento, dim))
	{
		ripristina_(sovrascritti, matrice);
		return (0);
	}
	return (1);
}

int	check_opps(char *matrice, int start, int incremento, int dim)
{
	return (check_opp(matrice, start, incremento, dim)
		&& check_opp(matrice, respective_opp(start, incremento, dim), incremento * -1, dim));
}

int	respective_opp(int start, int incremento, int dim)
{
	if (incremento == 4)
		return start + dim * (dim - 1);
	return start + dim - 1;
}

int	check_opp(char *matrice, int start, int incremento, int dim)
{
	char	prev_high;
	int	counter;
	int	i;

	prev_high = matrice[start];
	counter = 1;
	i = 0;
	while (++i < dim)
		if (matrice[start + incremento * i] > prev_high)
		{
			prev_high = matrice[start + incremento * i];
			counter++;
		}
	return counter == matrice[respective_check(start, incremento, dim) + dim * dim] - '0';
}

int	respective_check(int start, int incremento, int dim)
{
	if (incremento == dim)
		return start;
	else if (incremento == 1)
		return start / dim + dim * 2;
	else if (incremento == -1)
		return start / dim + dim * 3;
	else
		return start % dim + dim;
}

void	perm_(char *mancanti, int *dir, int size)
{
	char	mobile;
	int	pos;
	int	i;

	mobile = mobile_(mancanti, dir, size);
	pos = pos_(mancanti, size, mobile);
	if (dir[mancanti[pos] - '1'] == 0)
		swap(mancanti, pos, pos - 1);
	else
		swap(mancanti, pos, pos + 1);
	i = -1;
	while (++i < size)
	{
		if (mancanti[i] > mobile)
		{
			if (dir[mancanti[i] - '1'] == 1)
				dir[mancanti[i] - '1'] = 0;
			else
				dir[mancanti[i] - '1'] = 1;
		}
	}
}

char	mobile_(char *mancanti, int *dir, int size)
{
	char	mobile;
	int	i;

	mobile = '0';
	i = -1;
	while (++i < size)
	{
		if (i != 0 && dir[mancanti[i] - '1'] == 0 && mancanti[i] > mancanti[i - 1]
		&& mancanti[i] > mobile)
			mobile = mancanti[i];
		if (i != size - 1 && dir[mancanti[i] - '1'] == 1 && mancanti[i] > mancanti[i + 1]
		&& mancanti[i] > mobile)
			mobile = mancanti[i];
	}
	return (mobile);
}

int	pos_(char *mancanti, int size, char mobile)
{
	int	i;

	i = -1;
	while (++i < size)
		if (mancanti[i] == mobile)
			return (i);
	return (0);
}

void	swap(char *mancanti, int pos1, int pos2)
{
	char	temp;

	temp = mancanti[pos1];
	mancanti[pos1] = mancanti[pos2];
	mancanti[pos2] = temp;
}

void	ripristina_(int *sovrascritti, char *matrice)
{
	int	i;

	i = -1;
	while (++i < sovrascritti[0])
		matrice[sovrascritti[i + 1]] = '0';
}

int	mancanti_quanti_sono(char *matrice, int dim, int index, int incremento)
{
	int	counter;
	int	i;

	counter = 0;
	i = -1;
	if (incremento == 1)
		index *= 4;
	while(++i < dim)
		if (matrice[index + incremento * i] == '0')
			counter++;
	return (counter);
}

void	trova_mancanti(char *mancanti, char *matrice, int dim, int index, int incremento)
{
	int	i;
	int	j;
	int	flag;
	int	counter;

	counter = 0;
	i = 0;
	if (incremento == 1)
		index *= 4;
	while(counter < mancanti[0])
	{
		flag = 1;
		j = -1;
		i++;
		while(++j < dim)
			if (matrice[index + j * incremento] == i + '0')
			{
				flag = 0;
				break;
			}
		if (flag)
			counter = manca_(mancanti, i, counter);
	}
}

int	manca_(char *mancanti, int i, int counter)
{
	mancanti[counter + 1] = i + '0';
	return (counter + 1);
}
