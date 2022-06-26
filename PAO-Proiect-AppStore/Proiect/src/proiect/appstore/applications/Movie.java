package proiect.appstore.applications;

import proiect.service.AuditService;

public class Movie extends Application{
    private String directorName, subtitles;
    private boolean forKids;
    private AuditService auditService = AuditService.getAuditService();

    // CONSTRUCTORS

    public Movie(){
        this("", "", false);
        this.type = "Movie";
        auditService.writeData("Movie - add");
    }

    public Movie(String directorName, String subtitles, boolean forKids) {
        super("", "", 0);
        this.directorName = directorName;
        this.subtitles = subtitles;
        this.forKids = forKids;
        this.type = "Movie";
        auditService.writeData("Movie - add");
    }

    public Movie(String publisherName, String applicationName, float price, String directorName, String subtitles, boolean forKids) {
        super(publisherName, applicationName, price);
        this.directorName = directorName;
        this.subtitles = subtitles;
        this.forKids = forKids;
        this.type = "Movie";
        auditService.writeData("Movie - add");
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
