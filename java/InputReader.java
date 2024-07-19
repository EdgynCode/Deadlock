import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class InputReader {
    public static int[][] readMatrix(String fileName) throws IOException {
        List<int[]> matrixList = new ArrayList<>();
        BufferedReader br = new BufferedReader(new FileReader(fileName));

        String line;
        while ((line = br.readLine()) != null) {
            String[] values = line.split("\\s+"); // Split by whitespace
            int[] row = new int[values.length];
            for (int i = 0; i < values.length; i++) {
                row[i] = Integer.parseInt(values[i]);
            }
            matrixList.add(row);
        }
        br.close();

        int[][] matrix = new int[matrixList.size()][];
        for (int i = 0; i < matrixList.size(); i++) {
            matrix[i] = matrixList.get(i);
        }

        return matrix;
    }

    public static List<Integer> readList(String fileName) throws IOException {
        List<Integer> numberList = new ArrayList<>();
        BufferedReader br = new BufferedReader(new FileReader(fileName));
        String line = br.readLine();

        if (line != null) {
            String[] values = line.split("\\s+"); // Split by whitespace
            for (String value : values) {
                numberList.add(Integer.parseInt(value));
            }
        }

        br.close();

        return numberList;
    }

    public static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            for (int value : row) {
                System.out.print(value + " ");
            }
            System.out.println();
        }
    }

    public static void printList(List<Integer> list) {
        for (int number : list) {
            System.out.print(number + " ");
        }
        System.out.println();
    }
}
