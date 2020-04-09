package proiect.appstore.applications;

public class Game extends Application {
    private String genre;
    private boolean isMultiplayer;

    //CONSTRUCTORS

    public Game() {
        this("", false);
    }

    public Game(String genre, boolean isMultiplayer) {
        super("","", 0);
        this.genre = genre;
        this.isMultiplayer = isMultiplayer;
    }

    public Game(String publisherName, String applicationName, float price, String genre, boolean isMultiplayer) {
        super(publisherName, applicationName, price);
        this.genre = genre;
        this.isMultiplayer = isMultiplayer;
    }

    // SETTERS AND GETTERS

    public String getGenre() { return genre; }

    public void setGenre(String genre) {
        this.genre = genre;
    }

    public boolean isMultiplayer() {
        return isMultiplayer;
    }

    public void setMultiplayer(boolean multiplayer) {
        isMultiplayer = multiplayer;
    }
}
