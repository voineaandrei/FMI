package proiect.appstore.applications;

public class Application {
    protected String publisherName, applicationName;
    protected float price;
    protected Details details;
    protected String type;
    // CONSTRUCTORS

    public Application(){
        this("", "", 0);
        this.type = "";
    }

    public Application(String publisherName, String applicationName, float price) {
        this.publisherName = publisherName;
        this.applicationName = applicationName;
        this.price = price;
        this.type = "";
        this.details = new Details();
    }

    @Override
    public String toString() {
        return applicationName + ";";
    }

    // SETTERS AND GETTERS

    public String getPublisherName() {
        return publisherName;
    }

    public void setPublisherName(String publisherName) {
        this.publisherName = publisherName;
    }

    public String getApplicationName() {
        return applicationName;
    }

    public void setApplicationName(String applicationName) {
        this.applicationName = applicationName;
    }

    public float getPrice() {
        return price;
    }

    public void setPrice(float price) {
        this.price = price;
    }

    public Details getDetails() {
        return details;
    }

    public void setDetails(Details details) {
        this.details = details;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
}