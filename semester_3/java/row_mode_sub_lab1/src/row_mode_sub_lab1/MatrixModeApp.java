package row_mode_sub_lab1;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;

public class MatrixModeApp {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Введите размерность матрицы n: ");
        if (!scanner.hasNextInt()) {
            System.out.println("Ошибка: введено не целое число.");
            return;
        }
        
        int n = scanner.nextInt();
        if (n <= 0) {
            System.out.println("Ошибка: размерность матрицы должна быть больше нуля.");
            return;
        }

        int[][] matrix = new int[n][n];
        int[][] resultMatrix = new int[n][n];
        Random random = new Random();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = random.nextInt() % (n+1);
                resultMatrix[i][j] = matrix[i][j];
            }
        }

        System.out.println("\n\n--- Поиск мод в строке ---");

        for (int i = 0; i < n; i++) {
            int[] row = matrix[i];
            
            Map<Integer, Integer> frequencyMap = new HashMap<>();
            for (int val : row) {
                frequencyMap.put(val, frequencyMap.getOrDefault(val, 0) + 1);
            }

            int maxFreq = 0;
            int bestMode = 0;
            int modeCount = 0;

            for (Map.Entry<Integer, Integer> entry : frequencyMap.entrySet()) {
                int freq = entry.getValue();
                if (freq > maxFreq) {
                    maxFreq = freq;
                    bestMode = entry.getKey();
                    modeCount = 1;
                } else if (freq == maxFreq) {
                    modeCount++;
                }
            }

            if (maxFreq == 1) {
                System.out.println("Строка " + (i + 1) + ": Решение отсутствует. Все элементы уникальны.");
            } else if (modeCount > 1) {
                System.out.println("Строка " + (i + 1) + ": Решение отсутствует. Несколько элементов имеют одинаковую максимальную частоту.");
            } else {
                System.out.println("Строка " + (i + 1) + ": Найден мод = " + bestMode + " (встречается " + maxFreq + " раз(а)).");
                
                for (int j = 0; j < n; j++) {
                    resultMatrix[i][j] = matrix[i][j] - bestMode;
                }
            }
        }

        System.out.println("\n--- Исходная матрица ---");
        printMatrix(matrix);

        System.out.println("\n--- Результирующая матрица ---");
        printMatrix(resultMatrix);
        
        scanner.close();
    }

    private static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            System.out.println(Arrays.toString(row));
        }
    }
}