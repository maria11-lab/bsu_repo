int n = 5;
string[] conditions = { "Хорошее", "Нормальное", "Плохое" };
string[] grade = { "Наблюдать", "Ремонтировать", "Заменить" };

Random random = new Random();
double[] array = new double[n];
for (int i = 0; i < array.Length; i++)
{
    array[i] = random.NextDouble(); // от 0.0 до 1.0
}
foreach (double num in array)
{
    if (num >= 0.0 && num <= 0.4)
    {
        Console.WriteLine($"Состояние {conditions[0]} значит {grade[0]}");
    }
    if (0.4 < num && num <= 0.7)
    {
        Console.WriteLine($"Состояние {conditions[1]} значит {grade[1]}");
    }
    if (0.7 < num && num <= 1.0)
    {
        Console.WriteLine($"Состояние {conditions[2]} значит {grade[2]}");
    }
}