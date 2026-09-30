import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class text {

    private static final Pattern SENTENCE_SPLIT = Pattern.compile("(?<=[.!?])\\s+");

    private static final Pattern WORD = Pattern.compile("[\\p{L}\\p{N}]+(?:[-'][\\p{L}\\p{N}]+)*");

    private final List<String> sentences = new ArrayList<>();


    public text() {
        checkInvariant();
    }

    public text(String rawText) {
        if (rawText == null) {
            throw new IllegalArgumentException("Строка текста не может быть null");
        }
        String trimmed = rawText.trim();
        if (!trimmed.isEmpty()) {
            for (String part : SENTENCE_SPLIT.split(trimmed)) {
                sentences.add(normalize(part));
            }
        }
        checkInvariant();
    }

    public text(List<String> sentenceList) {
        if (sentenceList == null) {
            throw new IllegalArgumentException("Список предложений не может быть null");
        }
        for (String s : sentenceList) {
            sentences.add(normalize(s));
        }
        checkInvariant();
    }

    public text(text other) {
        if (other == null) {
            throw new IllegalArgumentException("Копируемый текст не может быть null");
        }
        sentences.addAll(other.sentences);
        checkInvariant();
    }


    public void addSentence(String sentence) {
        sentences.add(normalize(sentence));
        checkInvariant();
    }


    public String removeSentence(int index) {
        checkIndex(index, sentences.size());
        String removed = sentences.remove(index);
        checkInvariant();
        return removed;
    }


    public void insertSentence(int index, String sentence) {
        checkIndex(index, sentences.size() + 1);
        sentences.add(index, normalize(sentence));
        checkInvariant();
    }

    public String getSentence(int index) {
        checkIndex(index, sentences.size());
        return sentences.get(index);
    }

    public List<String> getSentences() {
        return Collections.unmodifiableList(new ArrayList<>(sentences));
    }


    public int getSentenceCount() {
        return sentences.size();
    }

    public int getWordCount() {
        int count = 0;
        for (String s : sentences) {
            Matcher m = WORD.matcher(s);
            while (m.find()) {
                count++;
            }
        }
        return count;
    }

    public int getLetterCount() {
        int count = 0;
        for (String s : sentences) {
            for (int i = 0; i < s.length(); i++) {
                if (Character.isLetter(s.charAt(i))) {
                    count++;
                }
            }
        }
        return count;
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof text)) return false;
        return sentences.equals(((text) o).sentences);
    }

    @Override
    public int hashCode() {
        return sentences.hashCode();
    }

    @Override
    public String toString() {
        return String.join(" ", sentences);
    }


    private static String normalize(String s) {
        if (s == null) {
            throw new IllegalArgumentException("Предложение не может быть null");
        }
        String t = s.trim();
        if (t.isEmpty()) {
            throw new IllegalArgumentException("Предложение не может быть пустым");
        }
        char last = t.charAt(t.length() - 1);
        if (last != '.' && last != '!' && last != '?') {
            t = t + ".";
        }
        return t;
    }

    private static void checkIndex(int index, int bound) {
        if (index < 0 || index >= bound) {
            throw new IndexOutOfBoundsException(
                    "Индекс " + index + " вне диапазона [0, " + (bound - 1) + "]");
        }
    }

    private void checkInvariant() {
        for (String s : sentences) {
            assert s != null && !s.isBlank() : "Нарушен инвариант: пустое предложение";
            assert ".!?".indexOf(s.charAt(s.length() - 1)) >= 0
                    : "Нарушен инвариант: предложение без конечного знака: " + s;
        }
    }
}