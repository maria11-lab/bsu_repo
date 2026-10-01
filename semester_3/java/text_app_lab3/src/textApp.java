import java.util.Arrays;

public class textApp {

    public static void main(String[] args) {

        System.out.println("=== Конструкторы ===");
        text t1 = new text();
        System.out.println("text():       \"" + t1 + "\", предложений: " + t1.getSentenceCount());

        text t2 = new text("Привет, мир! Как дела? Всё хорошо.");
        System.out.println("text(String): " + t2);
        System.out.println("предложений: " + t2.getSentenceCount());

        text t3 = new text(Arrays.asList("Первое", "Второе!"));
        System.out.println("text(List):   " + t3);

        text t4 = new text(t2);
        System.out.println("text(text):   " + t4);

        System.out.println("\n=== addSentence ===");
        t1.addSentence("Раз.");
        t1.addSentence("Два!");
        System.out.println(t1);

        System.out.println("\n=== insertSentence ===");
        t1.insertSentence(1, "Между ними.");
        System.out.println(t1);

        System.out.println("\n=== removeSentence ===");
        String removed = t1.removeSentence(1);
        System.out.println("Удалено: " + removed);
        System.out.println("Осталось: " + t1);

        System.out.println("\n=== Подсчёт ===");
        text t5 = new text("Hello, world! Это тест-проверка. Раз два три?");
        System.out.println("Текст: " + t5);
        System.out.println("Предложений: " + t5.getSentenceCount());
        System.out.println("Слов: " + t5.getWordCount());
        System.out.println("Букв: " + t5.getLetterCount());

        System.out.println("\n=== equals ===");
        text a = new text("Один. Два.");
        text b = new text("Один.   Два.");
        text c = new text("Два. Один.");
        System.out.println("a equals b: " + a.equals(b));   // true
        System.out.println("a equals c: " + a.equals(c));   // false

        System.out.println("\n=== Ошибки ===");
        try {
            new text((String) null);
        } catch (IllegalArgumentException e) {
            System.out.println("Ошибка: " + e.getMessage());
        }

        try {
            t1.addSentence("   ");
        } catch (IllegalArgumentException e) {
            System.out.println("Ошибка: " + e.getMessage());
        }

        try {
            t1.removeSentence(10);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Ошибка: " + e.getMessage());
        }

        try {
            t1.insertSentence(10, "Тест.");
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Ошибка: " + e.getMessage());
        }

        try {
            t1.getSentence(-1);
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Ошибка: " + e.getMessage());
        }
    }
}