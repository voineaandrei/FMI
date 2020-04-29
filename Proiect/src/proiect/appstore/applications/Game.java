package proiect.appstore.applications;

import proiect.service.AuditService;

public class Game extends Application {
    private String genre;
    private boolean isMultiplayer;
    private AuditService auditService = AuditService.getAuditService();

    //CONSTRUCTORS

    public Game() {
        this("", false);
        this.type = "Game";
        auditService.writeData("Game - add");
    }

    public Game(String genre, boolean isMultiplayer) {
        super("","", 0);
        this.genre = genre;
        this.isMultiplayer = isMultiplayer;
        this.type = "Game";
        auditService.writeData("Game - add");
    }

    public Game(String publisherName, String applicationName, float price, String genre, boolean isMultiplayer) {
        super(publisherName, applicationName, price);
        this.genre = genre;
        this.isMultiplayer = isMultiplayer;
        this.type = "Game";
        auditService.writeData("Game - add");
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
