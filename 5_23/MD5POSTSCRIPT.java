import java.security.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.Path;
import java.util.*;
import java.io.*;

public class MD5POSTSCRIPT{
  public static void main(String args[]) throws NoSuchAlgorithmException,IOException{


    MessageDigest md = MessageDigest.getInstance("MD5");

    byte[] bytesOfMessage = Files.readAllBytes(Paths.get("./auth2.ps"));
    System.out.println(Arrays.toString(md.digest(bytesOfMessage)));

    byte[] bytesOfMessageRec2 = Files.readAllBytes(Paths.get("./rec2.ps"));
    System.out.println(Arrays.toString(md.digest(bytesOfMessageRec2)));

    byte[] bytesOfMessage3 = Files.readAllBytes(Paths.get("./rec2Modified.ps"));
    System.out.println(Arrays.toString(md.digest(bytesOfMessage3)));

    byte[] bytesOfMessageRec4 = Files.readAllBytes(Paths.get("./rec2Modified.ps"));
    System.out.println(Arrays.toString(md.digest(bytesOfMessageRec4)));



  }
}
