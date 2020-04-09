package proiect.appstore.applications;

public class Audiobook extends Application {
    private String narratedBy;
    private int duration;

    // CONSTRUCTORS

    public Audiobook() {
        this("", 0);
    }

    public Audiobook(String narratedBy, int duration) {
        super("", "", 0);
        this.narratedBy = narratedBy;
        this.duration = duration;
    }

    public Audiobook(String publisherName, String applicationName, float price, String narratedBy, int duration) {
        super(publisherName, applicationName, price);
        this.narratedBy = narratedBy;
        this.duration = duration;
    }

    // SETTERS AND GETTERS

    public String getNarratedBy() {
        return narratedBy;
    }

    public void setNarratedBy(String narratedBy) {
        this.narratedBy = narratedBy;
    }

    public int getDuration() {
        return duration;
    }

    public void setDuration(int duration) {
        this.duration = duration;
    }
}
