package case_swap_lab2;
import java.util.Scanner;

class case_swap_lab2 {

    public static void main(String[] args) {

        Scanner in = new Scanner(System.in);

        while (in.hasNextLine()) {
            String line = in.nextLine();
            System.out.println(process(line));
        }

        in.close();
    }

    private static String process(String line) {

        StringBuilder sb = new StringBuilder();

        boolean wordStart = true;

        for (int i = 0; i < line.length(); i++) {

            char c = line.charAt(i);

            if (Character.isLetter(c)) {
                if (wordStart) {
                    if (Character.isUpperCase(c))
                        sb.append(Character.toLowerCase(c));
                    else
                        sb.append(Character.toUpperCase(c));
                    wordStart = false;
                } else {
                    sb.append(c);
                }
            } else {
                sb.append(c);
                wordStart = true;
            }
        }

        return sb.toString();
    }
}