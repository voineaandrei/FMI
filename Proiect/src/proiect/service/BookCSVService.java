package proiect.service;


import proiect.appstore.applications.Application;
import proiect.appstore.applications.Book;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class BookCSVService {

    public static BookCSVService bookCSVService = new BookCSVService();
    ApplicationService applicationService = ApplicationService.getApplicationService();

    public static BookCSVService getBookCSVService() {
        return bookCSVService;
    }

    public void readData() {
        Path path = Paths.get("Book.csv");
        try (var input = Files.newBufferedReader(path)) {
            String line;
            int noLine = 0;
            while ((line = input.readLine()) != null){
                String[] value = line.split(",");
                applicationService.add(new Book(value[0], value[1], Float.parseFloat(value[2]), Integer.parseInt(value[3]), value[4], value[5]));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void writeData(){
        Path path = Paths.get("Book.csv");
        try (var output = Files.newBufferedWriter(path)) {
            for (Book book : applicationService.getBooks()) {
                output.write(book.getPublisherName());
                output.write(",");
                output.write(book.getApplicationName());
                output.write(",");
                output.write(Float.toString(book.getPrice()));
                output.write(",");
                output.write(Integer.toString(book.getNumberOfPages()));
                output.write(",");
                output.write(book.getGenre());
                output.write(",");
                output.write(book.getAuthor());
                output.newLine();
                output.flush();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
