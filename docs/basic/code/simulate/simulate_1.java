import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int u = input.nextInt();
        int d = input.nextInt();
        int n = input.nextInt();
        int time = 0, dist = 0;
        while (true) {  // enumerate with an infinite loop
            dist += u;
            time++;
            if (dist >= n) {
                break;  // leave the loop once the condition holds
            }
            dist -= d;
        }
        System.out.println(time);   // print the result
        input.close();
    }
}
