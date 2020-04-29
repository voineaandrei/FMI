package proiect.service;

import proiect.appstore.applications.Application;
import proiect.appstore.user.Card;
import proiect.appstore.user.User;
import proiect.repository.UserRepository;

import java.util.List;


public class UserService {
    private static UserService userService = new UserService();
    private UserRepository userRepository = new UserRepository();
    private ApplicationService applicationService = ApplicationService.getApplicationService();
    private AuditService auditService = AuditService.getAuditService();

    public static UserService getUserService(){
        return userService;
    }

    public void add(User user) {
        auditService.writeData("User - add");
        userRepository.add(user);
    }

    public void add(List<User> users) {
        auditService.writeData("User - add");
        userRepository.add(users);
    }

    public boolean existsUser(String username){
        auditService.writeData("User - existsUser");
        for (User user : userRepository.getUsers())
            if (user.getUsername().equalsIgnoreCase(username))
                return true;
            return false;
    }

    public void addCard(String username, Card card) {
        auditService.writeData("User - addCard");
        for (User user : userRepository.getUsers())
            if (user.getUsername().equalsIgnoreCase(username)) {
                user.setCard(card);
                break;
            }
    }

    public void buyApplication(String username, String applicationName) {
        auditService.writeData("User - buyApplication");
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
        auditService.writeData("User - giveRating");
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

    public List<User> getUsers(){
        auditService.writeData("User - getUsers");
        return userRepository.getUsers();
    }

    public void showUsers(){
        auditService.writeData("User - showUsers");
        for (User user : userRepository.getUsers())
            System.out.println(user.toString());
    }
}
