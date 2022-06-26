package proiect.repository;

import proiect.appstore.applications.Application;

import java.util.ArrayList;
import java.util.List;

public class ApplicationRepository {
    private List<Application> applications = new ArrayList<>();

    public void addApplication(Application application){
        applications.add(application);
    }

    public void addApplications(List<Application> applications){
        this.applications.addAll(applications);
    }

    public List<Application> getApplications() {
        return applications;
    }
}
