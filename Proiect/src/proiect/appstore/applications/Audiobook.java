package proiect.appstore.applications;

import proiect.service.AuditService;

public class Audiobook extends Application {
    private String narratedBy;
    private int duration;
    private AuditService auditService = AuditService.getAuditService();

    // CONSTRUCTORS

    public Audiobook() {
        this("", 0);
        this.type = "Audiobook";
        auditService.writeData("Audiobook - add");
    }

    public Audiobook(String narratedBy, int duration) {
        super("", "", 0);
        this.narratedBy = narratedBy;
        this.duration = duration;
        this.type = "Audiobook";
        auditService.writeData("Audiobook - add");
    }

    public Audiobook(String publisherName, String applicationName, float price, String narratedBy, int duration) {
        super(publisherName, applicationName, price);
        this.narratedBy = narratedBy;
        this.duration = duration;
        this.type = "Audiobook";
        auditService.writeData("Audiobook - add");
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
