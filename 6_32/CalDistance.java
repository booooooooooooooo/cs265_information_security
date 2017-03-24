import java.math.BigInteger;
public class CalDistance{
  public static void main(String args[]){
    String alice = (new BigInteger("be439ad598ef5147", 16)).toString(2);
    String bob = (new BigInteger("9c8b7a1425369584", 16)).toString(2) ;
    String charlie = (new BigInteger("885522336699ccbb", 16) ).toString(2) ;

    String u = (new BigInteger("c975a2132e89ceaf", 16) ).toString(2);
    String v = (new BigInteger("db9a8675342fec15", 16) ).toString(2);
    String w = (new BigInteger("a6039ad5f8cfd965", 16) ).toString(2);
    String x = (new BigInteger("1dca7a54273497cc", 16) ).toString(2);
    String y = (new BigInteger("af8b6c7d5e3f0f9a", 16) ).toString(2);

    // System.out.println(alice);
    // System.out.println(bob);
    // System.out.println(charlie);

    String[] targets = {alice, bob, charlie};
    String[] targetsNames = {"alice", "bob", "charlie"};
    String[] users = {u, v, w, x, y};
    String[] usersNames = {"u", "v","w", "x", "y"};

    for(int i = 0; i < targets.length; i++){
      for(int j = i + 1; j < targets.length; j++){
        System.out.printf("d(%s, %s): %.2f\n", targetsNames[i], targetsNames[j], distance(targets[i],targets[j]));
      }
    }

    for(int i = 0; i < targets.length; i++){
      for(int j = 0; j < users.length; j++){
        System.out.printf("d(%s, %s): %.2f\n", targetsNames[i], usersNames[j], distance(targets[i],users[j]));
      }
      System.out.println();
    }
  }

  public static double distance(String s1, String s2){


    int count = 0;
    int i1 = s1.length() - 1;
    int i2 = s2.length() - 1;

    while(i1 >= 0 && i2 >= 0){
      if(s1.charAt(i1) != s2.charAt(i2)){
        count++;
      }
      i1--;
      i2--;
    }
    count += Math.abs(i1 - i2);
    return (double)count / 64;
  }
}
