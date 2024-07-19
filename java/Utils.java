import java.util.List;

public class Utils {
    public static boolean compare(List<Integer> lst, int R, int[][] matrix, int i) {
        for (int j = 0; j < R; j++) {
            if (lst.get(j) > matrix[i][j]) {
                return false;
            }
        }
        return true;
    }

    public static boolean compare(List<Integer> request, List<Integer> available, int R) {
        for (int j = 0; j < R; j++) {
            if (request.get(j) > available.get(j)) {
                return false;
            }
        }
        return true;
    }
}
