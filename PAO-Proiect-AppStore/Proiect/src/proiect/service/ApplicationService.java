package proiect.service;

import proiect.appstore.applications.*;
import proiect.repository.ApplicationRepository;

import java.util.ArrayList;
import java.util.List;

public class ApplicationService {
    private static ApplicationService applicationService = new ApplicationService();
    private ApplicationRepository applicationRepository = new ApplicationRepository();
    private AuditService auditService = AuditService.getAuditService();

    public static ApplicationService getApplicationService() {
        return applicationService;
    }

    public void add(Application application){
        applicationRepository.addApplication(application);
    }

    public void add(List<Application> applications){
        applicationRepository.addApplications(applications);
    }

    public void showRating(String applicationName){
        auditService.writeData("Application - showRating");
        for (Application app : applicationRepository.getApplications()){
            if (app.getApplicationName().equalsIgnoreCase(applicationName)) {
                if (app.getDetails().numberOfVotes != 0)
                    System.out.println(app.getDetails().rating/app.getDetails().numberOfVotes);
                else
                    System.out.println("Nu a primit niciun vot");
            }
        }
    }

    public boolean existsApplication(String applicationName){
        auditService.writeData("Application - existsApplication");
        for (Application app : applicationRepository.getApplications())
            if (app.getApplicationName().equalsIgnoreCase(applicationName))
                return true;
            return false;
    }

    public void showApplications(){
        List <Application> applications = getApplications();
        for (Application app : applications){
            System.out.println(app);
        }
    }

    public List<Application> getApplications(){
        auditService.writeData("Application - getApplications");
        return applicationRepository.getApplications();
    }

    public List<Audiobook> getAudiobooks() {
        auditService.writeData("Application - getAudiobooks");

        List <Audiobook> audiobooks = new ArrayList<>();
        for (Application app : applicationRepository.getApplications()) {
            if (app.getType() == "Audiobook")
                audiobooks.add((Audiobook) app);
        }
        if (audiobooks.size() != 0)
            auditService.writeData("Audiobook - writeData");
        return audiobooks;
    }

    public List<Book> getBooks() {
        auditService.writeData("Application - getBooks");

        List<Book> books = new ArrayList<>();
        for (Application app : applicationRepository.getApplications()){
            if (app.getType() == "Book")
                books.add((Book) app);
        }
        if (books.size() != 0)
            auditService.writeData("Book - writeData");
        return books;
    }

    public List<Movie> getMovies() {
        auditService.writeData("Application - getMovie");

        List <Movie> movies = new ArrayList<>();
        for (Application app : applicationRepository.getApplications()) {
            if (app.getType() == "Movie")
                movies.add((Movie) app);
        }
        if (movies.size() != 0)
            auditService.writeData("Movie - writeData");
        return movies;
    }

    public List<Game> getGames() {
        auditService.writeData("Application - getGame");

        List <Game> games = new ArrayList<>();
        for (Application app : applicationRepository.getApplications()){
            if (app.getType() == "Game")
                games.add((Game) app);
        }
        if (games.size() != 0)
                auditService.writeData("Game - writeData");
        return games;
    }
}
