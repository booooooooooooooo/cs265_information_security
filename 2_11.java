import java.util.*;
import java.io.*;
public class Chapter2_12 {
  private static final String RelativeFreq = "etaoinshrdlcumwfgypbvkjxqz";
  public static void main(String args[]) throws FileNotFoundException{
    String ciphertext = "";
    Scanner fin = new Scanner(new File("input"));
    while(fin.hasNext()){
      ciphertext += fin.nextLine();
    }
    ciphertext.replaceAll("\\s+", "");
    System.out.println(ciphertext);
    String cipherFreq = getCipherFreq(ciphertext);
    System.out.println(cipherFreq);
    while (true) {
      Map<String, String> key = getKeyFromInput(cipherFreq);
      String plaintext = getPlaintext(key, ciphertext);
      System.out.println("****The plaintext using your key****\n" + plaintext);
    }
  }

  public static String getCipherFreq(String ciphertext) {
    Map<String, Integer> freq = new HashMap<String, Integer>();
    for (int i = 0; i < ciphertext.length(); i++) {
      String key = "" + ciphertext.charAt(i);
      if (freq.containsKey(key))
        freq.put(key, freq.get(key) + 1);
      else
        freq.put(key, 1);
    }
    List<Tuple> freqList = new ArrayList<Tuple>();
    for (String key : freq.keySet()) {
      Tuple t = new Tuple(key.charAt(0), freq.get(key));
      freqList.add(t);
    }
    Collections.sort(freqList, new Comparator<Tuple>() {
      @Override
      public int compare(Tuple t1, Tuple t2) {
        return  -(t1.freq - t2.freq);
      }
    });

    String order = "";
    for (int i = 0; i < freqList.size(); i++)
      order = order + freqList.get(i).letter;
    return order;
  }

  public static Map<String, String> getKeyFromInput(String cipherFreq) {
    System.out.println("****Let us do crytoanalysis****");
    System.out.printf("Length of Key : %d\n",
                      cipherFreq.length());
    System.out.printf("Cipher Order: \n%s\n",
                      cipherFreq);
    System.out.printf(
        "General Order: \n%s\n",
        RelativeFreq);
    System.out.printf(
        "Your guess:\n");
    Scanner cin = new Scanner(System.in);
    String guess = cin.nextLine();
    Map<String, String> key = new HashMap<String, String>();
    for (int i = 0; i < cipherFreq.length(); i++) {
      key.put("" + cipherFreq.charAt(i), "" + guess.charAt(i));
    }
    return key;
  }

  public static String getPlaintext(Map<String, String> key,
                                    String ciphertext) {
    String plaintext = "";
    for (int i = 0; i < ciphertext.length(); i++) {
      String cipher = "" + ciphertext.charAt(i);
      plaintext += key.get(cipher);
    }
    return plaintext;
  }
}

class Tuple {
  public char letter;
  public int freq;
  public Tuple(char letter, int freq) {
    this.letter = letter;
    this.freq = freq;
  }
}
