package proiect.appstore.applications;

public class Movie extends Application{
    private String directorName, subtitles;
    private boolean forKids;


    // CONSTRUCTORS

    public Movie(){
        this("", "", false);
    }

    public Movie(String directorName, String subtitles, boolean forKids) {
        super("", "", 0);
        this.directorName = directorName;
        this.subtitles = subtitles;
        this.forKids = forKids;
    }

    public Movie(String publisherName, String applicationName, float price, String directorName, String subtitles, boolean forKids) {
        super(publisherName, applicationName, price);
        this.directorName = directorName;
        this.subtitles = subtitles;
        this.forKids = forKids;
    }
// SETTERS AND GETTERS

    public String getDirectorName() {
        return directorName;
    }

    public void setDirectorName(String directorName) {
        this.directorName = directorName;
    }

    public String getSubtitles() {
        return subtitles;
    }

    public void setSubtitles(String subtitles) {
        this.subtitles = subtitles;
    }

    public boolean isForKids() {
        return forKids;
    }

    public void setForKids(boolean forKids) {
        this.forKids = forKids;
    }
}
