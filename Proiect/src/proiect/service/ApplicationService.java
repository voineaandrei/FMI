package proiect.service;

import proiect.appstore.applications.Application;
import proiect.repository.ApplicationRepository;

import java.util.List;

public class ApplicationService {
    public static ApplicationService applicationService = new ApplicationService();
    private ApplicationRepository applicationRepository = new ApplicationRepository();

    public void add(Application application){
        applicationRepository.addApplication(application);
    }

    public void add(List<Application> applications){
        applicationRepository.addApplications(applications);
    }

    public void showRating(String applicationName){
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
        for (Application app : applicationRepository.getApplications())
            if (app.getApplicationName().equalsIgnoreCase(applicationName))
                return true;
            return false;
    }

    public List<Application> getApplications(){
        return applicationRepository.getApplications();
    }
}
