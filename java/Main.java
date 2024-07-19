import java.io.IOException;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);

        int[][] alloc = InputReader.readMatrix("alloc.txt");
        int[][] max = InputReader.readMatrix("max.txt");
        List<Integer> available = InputReader.readList("available.txt");
        int[][] request = InputReader.readMatrix("request.txt");

        int[][] need = Mechanics.calculateNeed(alloc, max);

        Mechanics.tableView(alloc, max, need, available);

        System.out.print("\n\n");

        System.out.println("1. Perform safety check.");
        System.out.println("2. Check if resources allocatable.");
        System.out.println("3. Deadlock detection.");
        System.out.println("0. Exit.");
        System.out.print("Choose an option: ");

        int n = scanner.nextInt();

        switch (n) {
            case 0:
                break;
            case 1:
                Mechanics.safetyCheck(alloc, need, available);
                break;
            case 2:
                System.out.print("Process number: ");
                int process = scanner.nextInt();
                Mechanics.resourceAllocation(alloc, max, need, available, process);
                break;
            case 3:
                Mechanics.tableView(alloc, max, need, request, available);
                boolean isDeadlocked = Mechanics.safetyCheck(alloc, need, available);
                String message = isDeadlocked ? "No deadlock detected." : "Deadlock detected.";
                System.out.print(message);
                break;
        }

        scanner.close();
    }
}
