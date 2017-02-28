import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import javax.swing.*;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
import java.io.IOException;
import javax.imageio.ImageIO;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;


public class Tea {
  public static void main(String args[]) {
    System.out.println("jpg or bmp?");
    Scanner cin = new Scanner(System.in);
    String format = cin.next();
    //read in image
    BufferedImage image = null;
    try {
      image = ImageIO.read(new File("alice." + format ));
    } catch (IOException e) {
    }
    //get pixels
    int width = image.getWidth();
    int height = image.getHeight();
    WritableRaster raster = image.getRaster();
    // System.out.println("width:" + width);
    // System.out.println("height:" + height);
    // System.out.println("Channels:" + raster.getNumDataElements());
    // System.out.println("NumBands:" + raster.getNumBands());

    int[] dummy = null;
    int[] threeChannelPixels = raster.getPixels(0, 0, width, height, dummy);


    //encrypt
    long[] keys = new long[4];
    for(int i = 0; i < 4; i++)
      keys[i] = Math.abs((new Random()).nextLong()) % ((long) (Math.pow(2, 32)));
    int[] ciphertext = ecb(threeChannelPixels, keys);
    raster.setPixels(0, 0, width, height, ciphertext);
    //write encryptedAlice.jpg to disk
    try {
      File outputfile = new File("encryptedAlice." + format  );
      ImageIO.write(image, format, outputfile);
    } catch (IOException e) {
    }
  }
  /* Each integer represents one byte. Key contains four integers.*/
  public static int[] ecb(int[] plaintext, long[] keys){
    //leave the first 10 blocks
    int[] ciphertext = new int[plaintext.length];
    System.arraycopy(plaintext, 0, ciphertext, 0, 80);
    //encrypt the rest
    int i = 81;
    while(i < plaintext.length){
      int[] plainBlk = new int[8];
      System.arraycopy(plaintext, i, plainBlk, 0, Math.min(8, plaintext.length - i));
      int[] cipherBlk = teaEytBlk(plainBlk, keys);
      // System.out.println(i);
      // System.out.println(ciphertext.length);
      // System.out.println(cipherBlk.length);
      System.arraycopy(cipherBlk, 0, ciphertext, i,  Math.min(8, ciphertext.length - i));
      i += 8;
    }
    return ciphertext;
  }
  /*
   * plainBlk has 8 R, G, or B.
   * keys has 4 key.
   */
  public static int[] teaEytBlk(int[] plainBlk, long[] keys){
    //convert four R, G or B to a long
    long l = 0;
    for(int i = 0; i < 4; i++)
      l = 32 * l + plainBlk[i];
    long r = 0;
    for(int i = 4; i < 8; i++)
      r = 32 * r + plainBlk[i];
    long delta = Long.parseLong("9e3779b9", 16);
    long sum = 0;
    //encrypt
    long modular = (long) (Math.pow(2, 32));
    for(int i = 0; i < 32; i++){
      sum = (sum + delta) % modular;
      l = ( l +  ( ((r << 4)+ keys[0]) ^ (r + sum) ^ ((r >> 5) + keys[1]) ) ) % modular;
      r = ( r + ( ( (l << 4) + keys[2]) ^ (l + sum) ^ ( (l >> 5) + keys[3] ) ) ) % modular;
    }
    //convert l and r to 8 R, G or B
    int[] cipherBlk = new int[8];
    for(int i = 3; i >= 0; i--){
      cipherBlk[i] = (int)(l % 256) ;
      l = l >> 8;
    }
    for(int i = 7; i >= 4; i--){
      cipherBlk[i] = (int)(r % 256);
      r = r >> 8;
    }
    return cipherBlk;
  }
}
