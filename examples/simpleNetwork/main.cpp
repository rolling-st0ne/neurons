
//
// Created by Irena Mora on 1/4/22.
//
//#include ".hpp"

#include <iostream>
#include "../../42neurons.hpp"

#include <sys/time.h>

using namespace std;

/* Получаем случайное число в диапазоне от 0 до 100 */
int getRandom()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	srand(time.tv_sec * time.tv_usec);
	return (rand() % 100);
}

int	main()
{
	/* Переменная, нужная в дальнейшем */
	int value;
	/* Переменная, нужная в дальнейшем */
	string line;
	/* Создаем один входящий нейрон */
	NeuronIn	in_first;
	/* Создаем один выходящий нейрон, где будет храниться наш результат */
	NeuronOut	out_first;
	/* Создаем нейронную сеть, которая будет соединять нейроны, обучаться и делать предсказания */
	NeuronNetwork network;

	/* Добавляем входной нейрон в нейронную сеть */
	network.addNeuron(in_first);
	/* Добавляем выходной нейрон в нейронную сеть */
	network.addNeuron(out_first);
	/* Устанавливаем соединение между входным и выходным нейронами; функция активации - ReLU; скорость обучения - 0.01; изначальный вес - 0.5*/
	network.createConnection(in_first, out_first, FunctionType::RELU, 0.01, 0.5);

	/* Выполняем 20 циклов обучения нейронной сети */
	for (int i = 0; i < 20; i++)
	{
		/* Получаем случайное число */
		value = getRandom();
		/* Устанавливаем полученное случайное число на входном нейроне */
		in_first.setStatus(value);
		/* Устанавливаем для выходного нейрона 'ожидаемый результат', чтобы нейронная сеть стремилась к нему при обучении */
		/* В данном случае ожидаемый результат - это value * 0.75 */
		out_first.setExpectedStatus(value * 0.75);
		/* Обучаем нейросеть */
		network.learn();
		/* Выводим на экран номер цикла обучения; ожидаемый результат, который установили ранее; результат, предсказанный нейронной сетью */
		cout	<< "Learning №" << i << ". "
				<< "Expected status " << out_first.getExpectedStatus() << ". "
				<< "Status " << out_first.getStatus() << endl;
		/* Повторяем цикл обучения. Со временем нейронная сеть обучается и предсказанный результат приближается к ожидаемому */
	}

	/* Выполняем вечный цикл */
	while (1)
	{
		/* Просим пользователя ввести число */
		cout << "Write value:" << endl;
		/* Кладём введенное число в переменную line */
		getline(cin, line);
		/* Переводим string в int */
		try
		{
			value = std::stoi(line);
		}
		catch (exception &e)
		{
			cout << "Error: value is not correct!" << endl;
			continue ;
		}
		/* Устанавливаем для входящего нейрона значение, равное ранее полученному из введенной пользователем строки */
		in_first.setStatus(value);
		/* Предсказываем ответ обученной ранее нейросетью */
		network.compute();
		/* Выводим предсказанный нейросетью ответ на экран */
		cout << "Your result: " << out_first.getStatus() << endl;
		/* Повторяем цикл с самого начала */
	}
}

/* ВАЖНО: нейронная сеть в качестве ответа будет выдавать nan, 0, другие неверные ответы, когда: */
/* 1. Неверно подобраны коэффициенты в функции createConnection */
/* 2. Обучающих циклов было недостаточно, либо они не были разнообразны */
/* 3. Нейронная сеть спроектирована неверно, а равно нейроны соединены нецелесообразными связями */
/* 4. Входных данных для обучения было недостаточно, а равно в действительности имеют место другие влияющие факторы, которые учтены не были */