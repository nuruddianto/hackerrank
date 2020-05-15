package code;

/**
 * Created by SRIN on 4/7/2017.
 */
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.stream.Stream;

public class ReadFile {

    public static void main(String[] args) {
		readFile();
        //walk();
    }

    public static void readFile(){
        try(BufferedReader br = new BufferedReader(new FileReader("D:\\Project\\NewEclipse\\hacker_rank\\src\\code\\MyLinkedList.java"))) {
            StringBuilder sb = new StringBuilder();
            String line = br.readLine();

            while (line != null) {
                sb.append(line);
                sb.append(System.lineSeparator());
                line = br.readLine();
            }
            String everything = sb.toString();
            System.out.println(everything);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    public static void walk(){
        try(Stream<Path> paths = Files.walk(Paths.get("D:/Project/NewEclipse"))) {
            paths.forEach(filePath -> {
                if (Files.isRegularFile(filePath)) {
                    System.out.println(filePath);
                }
            });
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
