package proiect.appstore.user;

import proiect.appstore.applications.*;

import java.util.ArrayList;
import java.util.List;

public class User {
    private static int idTotal = 0;
    private String lastName, firstName, username;
    private final int idCurrent = idTotal;
    private List<Application> applications = new ArrayList<>();
    private Card card;

    public User(){
        this("", "", "", null, null);
    }

    public User(String lastName, String firstName, String username) {
        this.lastName = lastName;
        this.firstName = firstName;
        this.username = username;
        this.idTotal += 1;
    }

    public User(String lastName, String firstName, String username, List<Application> applications, Card card) {
        this.lastName = lastName;
        this.firstName = firstName;
        this.username = username;
        this.applications = applications;
        this.card = card;
        this.idTotal += 1;
    }

    public boolean hasApplication(String applicationName){
        for (Application app : applications){
            if (app.getApplicationName().equalsIgnoreCase(applicationName)){
                return true;
            }
        }
        return false;
    }

    public void addApp(Application app){
        applications.add(app);
    }

    public void addApp(List<Application> apps){
        applications.addAll(apps);
    }

    @Override
    public String toString() {
        String toReturn = "Nume: " + lastName + " " + firstName + "\n" +
                "Username: " + username + '\n' +
                "Id-ul Userului: " + idCurrent + '\n';

        if (applications.size() != 0) {
            toReturn += "Aplicatii: ";
            for (Application app : applications) {
                toReturn += app.toString();
            }
            toReturn += '\n';
        }
        if (card != null) {
            toReturn += "Card: " + card.toString() + '\n';
        }
        return toReturn;
    }

    // SETTERS AND GETTERS

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public List<Application> getApplications() {
        return applications;
    }

    public void setApplications(List<Application> applications) {
        this.applications = applications;
    }

    public Card getCard() {
        return card;
    }

    public void setCard(Card card) {
        this.card = card;
    }

    public int getIdCurrent() {
        return idCurrent;
    }
}
