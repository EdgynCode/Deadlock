import java.util.List;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;

public class Mechanics {
    public static int[][] calculateNeed(int[][] alloc, int[][] max) {
        int rows = alloc.length;
        int cols = alloc[0].length;
        int[][] need = new int[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                need[i][j] = max[i][j] - alloc[i][j];
            }
        }

        return need;
    }

    public static void tableView(int[][] alloc, int[][] max, int[][] need, List<Integer> available) {
        int rows = alloc.length;
        int cols = alloc[0].length;

        System.out.print("Available: ");
        for (int i = 0; i < available.size(); i++)
            System.out.print(available.get(i) + " ");
        System.out.println();

        System.out.print("Alloc\t\tMax\t\tNeed\n");

        char[] dashes = new char[45];
        Arrays.fill(dashes, '-');
        System.out.println(new String(dashes));

        for (int i = 0; i < rows; i++) {
            // print alloc
            for (int j = 0; j < cols; j++) {
                System.out.print(alloc[i][j] + " ");
            }
            System.out.print("\t\t");
            // print max
            for (int j = 0; j < cols; j++) {
                System.out.print(max[i][j] + " ");
            }
            System.out.print("\t\t");
            // print need
            for (int j = 0; j < cols; j++) {
                System.out.print(need[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void tableView(int[][] alloc, int[][] max, int[][] need, int[][] request, List<Integer> available) {
        int rows = alloc.length;
        int cols = alloc[0].length;

        System.out.print("Available: ");
        for (int i = 0; i < available.size(); i++)
            System.out.print(available.get(i) + " ");
        System.out.println();

        System.out.print("Alloc\t\tMax\t\tNeed\t\tRequest\n");

        char[] dashes = new char[60];
        Arrays.fill(dashes, '-');
        System.out.println(new String(dashes));

        for (int i = 0; i < rows; i++) {
            // print alloc
            for (int j = 0; j < cols; j++) {
                System.out.print(alloc[i][j] + " ");
            }
            System.out.print("\t\t");
            // print max
            for (int j = 0; j < cols; j++) {
                System.out.print(max[i][j] + " ");
            }
            System.out.print("\t\t");
            // print need
            for (int j = 0; j < cols; j++) {
                System.out.print(need[i][j] + " ");
            }
            System.out.print("\t\t");
            // print request
            for (int j = 0; j < cols; j++) {
                System.out.print(request[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static boolean safetyCheck(int[][] alloc, int[][] need, List<Integer> available) {
        // init
        List<Integer> work = new ArrayList<>();
        List<Integer> safeSeq = new ArrayList<>();
        int P = alloc.length;
        int R = alloc[0].length;

        boolean[] finished = new boolean[alloc.length];

        // work = available
        for (int i = 0; i < available.size(); i++) {
            work.add(available.get(i));
        }

        // safe sequence init
        for (int i = 0; i < P; i++) {
            safeSeq.add(0);
        }

        // While all processes are not finished or system is not in safe state.
        int index = 0;
        while (index < P) {
            // Find a process which is not finish and whose needs can be satisfied with
            // current work[] resources.
            boolean found = false;
            for (int i = 0; i < P; i++) {
                // Check if a process is finished
                if (!finished[i]) {
                    // need[i] > work: break
                    int j;
                    for (j = 0; j < R; j++) {
                        if (need[i][j] > work.get(j)) {
                            break;
                        }
                    }

                    if (j == R) {
                        // free resources
                        for (int k = 0; k < R; k++) {
                            work.set(k, work.get(k) + alloc[i][k]);
                        }

                        // add to safe sequence
                        safeSeq.set(index, i);
                        index++;

                        // mark as finished
                        finished[i] = true;
                        found = true;
                    }
                }
            }
            if (!found) {
                System.out.println("System is not in a safe state");
                return false;
            }
        }

        System.out.print("System is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < P; i++) {
            System.out.print("P" + safeSeq.get(i) + " ");
        }

        return true;
    }

    public static boolean resourceAllocation(int[][] alloc, int[][] max, int[][] need, List<Integer> available, int i) {
        // int P = alloc.length;
        int R = alloc[0].length;

        List<Integer> request = new ArrayList<>();

        System.out.print("Request: ");
        Scanner scanner = new Scanner(System.in);
        for (int k = 0; k < R; k++) {
            int tmp = scanner.nextInt();
            request.add(tmp);
        }
        scanner.close();

        if (!Utils.compare(request, R, need, i)) {
            System.out.println("Overflow. Resources cannot be allocated.");
            return false;
        } else {
            if (Utils.compare(request, available, R)) {
                for (int j = 0; j < R; j++) {
                    available.set(j, available.get(j) - request.get(j));
                    alloc[i][j] += request.get(j);
                    need[i][j] -= request.get(j);
                }
                tableView(alloc, max, need, available);
                boolean isSafe = safetyCheck(alloc, need, available);
                if (isSafe) {
                    System.out.println("Resources allocated immediately.");
                    return true;
                } else {
                    for (int j = 0; j < R; j++) {
                        available.set(j, available.get(j) + request.get(j));
                        alloc[i][j] -= request.get(j);
                        need[i][j] += request.get(j);
                    }
                    System.out.println("Resources cannot be allocated immediately.");
                    return false;
                }
            } else {
                System.out.println("Resources cannot be allocated.");
                return false;
            }
        }
    }
}
