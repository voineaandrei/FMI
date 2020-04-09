package proiect.service;

import proiect.appstore.applications.Application;
import proiect.appstore.user.Card;
import proiect.appstore.user.User;
import proiect.repository.UserRepository;

import java.util.List;

import static proiect.service.ApplicationService.applicationService;


public class UserService {
    public static UserService userService = new UserService();
    private UserRepository userRepository = new UserRepository();

    public void add(User user) {
        userRepository.add(user);
    }

    public void add(List<User> users) {
        userRepository.add(users);
    }

    public boolean existsUser(String username){
        for (User user : userRepository.getUsers())
            if (user.getUsername().equalsIgnoreCase(username))
                return true;
            return false;
    }

    public void addCard(String username, Card card) {
        for (User user : userRepository.getUsers())
            if (user.getUsername().equalsIgnoreCase(username)) {
                user.setCard(card);
                break;
            }
    }

    public void buyApplication(String username, String applicationName) {
        if (!applicationService.existsApplication(applicationName)) {
            System.out.println("Nu exista aplicatia " + applicationName);
            return;
        }
        if (!existsUser(username)){
            System.out.println("Nu exista user-ul " + username);
            return;
        }
        for (User user : userRepository.getUsers())
            if (user.getUsername().equalsIgnoreCase(username)) {
                for (Application app : applicationService.getApplications()) {
                    if (app.getApplicationName().equalsIgnoreCase(applicationName))
                        if (user.getCard().getMoney() >= app.getPrice()) {
                            user.addApp(app);
                            user.getCard().setMoney(user.getCard().getMoney() - app.getPrice());
                            app.getDetails().numberOfDownloads += 1;
                            return;
                        }
                    else
                        {
                            System.out.println("User-ul " + username + "are doar " + user.getCard().getMoney() + ", iar jocul costa " + app.getPrice());
                            return;
                        }
                }
            }
    }

    public void giveRating(String username, String applicationName, int rating) {
        if (!applicationService.existsApplication(applicationName)) {
            System.out.println("Aplicatia " + applicationName + " nu exista");
            return;
        }
        if (!existsUser(username)){
            System.out.println("Nu exista user-ul " + username);
            return;
        }
        if (rating > 5 || rating <= 0){
            System.out.println("Rating-ul este incorect");
            return;
        }
        for (User user : userRepository.getUsers()) {
            if (user.getUsername().equalsIgnoreCase(username)) {
                if (user.hasApplication(applicationName)) {
                    for (Application app : user.getApplications()) {
                        if (app.getApplicationName().equalsIgnoreCase(applicationName)) {
                            app.getDetails().numberOfVotes += 1;
                            app.getDetails().rating += rating;
                            return;
                        }
                    }
                } else {
                    System.out.println("User-ul " + username + " nu are aplicatia " + applicationName);
                    return;
                }
            }
        }
    }

    public void showUsers(){
        for (User user : userRepository.getUsers())
            System.out.println(user.toString());
    }
}
