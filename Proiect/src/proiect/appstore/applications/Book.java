package proiect.appstore.applications;

public class Book extends Application {
    private int numberOfPages;
    private String genre, author;

    // CONSTRUCTORS

    public Book() {
        this(0, "", "");
    }

    public Book(int numberOfPages, String genre, String author) {
        super("", "", 0);
        this.numberOfPages = numberOfPages;
        this.genre = genre;
        this.author = author;
    }

    public Book(String publisherName, String applicationName, float price, int numberOfPages, String genre, String author) {
        super(publisherName, applicationName, price);
        this.numberOfPages = numberOfPages;
        this.genre = genre;
        this.author = author;
    }


    // SETTERS AND GETTERS

    public int getNumberOfPages() {
        return numberOfPages;
    }

    public void setNumberOfPages(int numberOfPages) {
        this.numberOfPages = numberOfPages;
    }

    public String getGenre() {
        return genre;
    }

    public void setGenre(String genre) {
        this.genre = genre;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }
}
