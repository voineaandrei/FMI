package proiect.appstore.applications;

public class Details {
    public int numberOfDownloads, numberOfVotes;
    public float rating;

    // CONSTRUCTORS

    public Details() {
        this(0, 0 ,0);
    }

    public Details(int numberOfDownloads, int numberOfVotes, float rating) {
        this.numberOfDownloads = numberOfDownloads;
        this.numberOfVotes = numberOfVotes;
        this.rating = rating;
    }


    // SETTERS AND GETTERS

    public int getNumberOfDownloads() {
        return numberOfDownloads;
    }

    public void setNumberOfDownloads(int numberOfDownloads) {
        this.numberOfDownloads = numberOfDownloads;
    }

    public int getNumberOfVotes() {
        return numberOfVotes;
    }

    public void setNumberOfVotes(int numberOfVotes) {
        this.numberOfVotes = numberOfVotes;
    }

    public float getRating() {
        return rating;
    }

    public void setRating(float rating) {
        this.rating = rating;
    }
}
