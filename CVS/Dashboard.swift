//
//  Dashboard.swift
//  CVS
//
//  Created by Nardos Hailu on 4/4/18.
//  Copyright © 2018 Nardos Hailu. All rights reserved.
//

import Foundation
import UIKit
import SwiftyJSON
import Alamofire
import Bots
import UserNotifications

class Dashboard: UIViewController {
    
    
    var mbe: OMCMobileBackend!;
    var auth: OMCAuthorization!;
    
    var defaults = UserDefaults.standard
    
    let appDelegate = UIApplication.shared.delegate as! AppDelegate
    
    @IBOutlet weak var scrollView: UIScrollView!
    @IBOutlet weak var greetingText: UILabel!
    @IBOutlet weak var stepsText: UILabel!
    @IBOutlet weak var caloriesText: UILabel!
    @IBOutlet weak var heartRateText: UILabel!
    @IBOutlet weak var bloodPressureText: UILabel!
    @IBOutlet weak var floorsText: UILabel!
    @IBOutlet weak var elevationText: UILabel!
    
    
    var fitBitSteps:String!
    @IBOutlet weak var userFirstName: UILabel!
    
    @IBOutlet weak var patientWeight: UILabel!
    @IBOutlet weak var patientHeight: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // initialize Bot
        Bots.initWith(OMCSettings(appId: "5c34cc1d5c3ec30022018153")) { (error: Error?, userInfo: [AnyHashable : Any]?) in
            print("Bot started by User")
            Bots.setUserFirstName("John", lastName: "Dunbar")
            //Bots.conversation()?.sendMessage(OMCMessage.init(text: "Session Began: "))
            
        }
        
        getBloodPressureData()
        self.navigationItem.hidesBackButton = true
        defaults.synchronize()
        patientWeight.text = String(defaults.integer(forKey: "PatientWeight"))
        patientHeight.text = String(defaults.double(forKey: "PatientHeight"))
        
        mbe = appDelegate.myMobileBackend()
        auth = mbe.authorization;
        print ("User authorized:  \(auth.authorized)")
        
        self.userFirstName.text = "John"
        /*
        if (auth.authorized){
            auth.getCurrentUser { (error, user) in
                print("USER FIRST NAME: \(String(describing: user!.firstName))")
                self.userFirstName.text = user?.firstName
            }
        }
         */

        displayGreeting()
        scrollView.contentSize = CGSize(width: self.view.frame.width, height:1200)

        // Token last changed: 04/02/2019. Set to expire every year!
        let headers = [
            "Authorization": "Bearer eyJhbGciOiJIUzI1NiJ9.eyJhdWQiOiIyMkNOR1giLCJzdWIiOiIzTVdQWTUiLCJpc3MiOiJGaXRiaXQiLCJ0eXAiOiJhY2Nlc3NfdG9rZW4iLCJzY29wZXMiOiJ3aHIgd3BybyB3bnV0IHdzbGUgd3dlaSB3c29jIHdhY3Qgd3NldCB3bG9jIiwiZXhwIjoxNTg1ODUzNDgzLCJpYXQiOjE1NTQzMTc0ODN9.Z9mMjbjtIEf-evIEZ8QA_J_bsA0qp8PB6EBQszj625E",
            "Cache-Control": "no-cache",
            "Postman-Token": "565454fa-33de-40d6-9f06-4f30f7e2ac5c"
        ]
        
        let request = NSMutableURLRequest(url: NSURL(string: "https://api.fitbit.com/1/user/-/activities/date/today.json")! as URL,
                                          cachePolicy: .useProtocolCachePolicy,
                                          timeoutInterval: 10.0)
        request.httpMethod = "GET"
        request.allHTTPHeaderFields = headers
        
        let session = URLSession.shared
        let dataTask = session.dataTask(with: request as URLRequest, completionHandler: { (data, response, error) -> Void in
            
            let json = JSON(data)
            let steps = json["summary"]["steps"].stringValue
            let calories = json["summary"]["caloriesBMR"].stringValue
            let elevation = json["summary"]["elevation"].stringValue
            let floors = json["summary"]["floors"].stringValue
            DispatchQueue.main.async { // Correct
                self.stepsText.text = steps
                self.caloriesText.text = calories
                self.elevationText.text = elevation
                self.floorsText.text = floors
            }

        })
        
        dataTask.resume()
       
    }

    func getBloodPressureData(){
        
        let url = "https://cvs-innovation.herokuapp.com/ihealth/lastReading"
        
        
        print("BLOOD PRESSURE READING")
        Alamofire.request(url).responseJSON { (response) in
            if let responseValue = response.result.value as? [String:AnyObject]{
                let heartRate:String = "\(responseValue["heartRate"]!)"
                self.heartRateText.text = heartRate
                let bloodPressure: String = "\(((responseValue["systolicPressure"]! )))/\(((responseValue["diastolicPressure"]!)))"
                self.bloodPressureText.text = bloodPressure
                print("BLOOD PRESSURE: \(bloodPressure)")
            }
        }
    }
    
    func displayGreeting(){
        let hour = Calendar.current.component(.hour, from: Date())
        
        if hour >= 0 && hour < 12 {
            greetingText.text = "Good Morning,"
        } else if hour >= 12 && hour < 17 {
            greetingText.text = "Good Afternoon,"
        } else if hour >= 17 {
           greetingText.text = "Good Evening,"
        }
    }
    
    @IBAction func askHelp(_ sender: Any) {
        // an icon that leads to the bot so the user can start conversation as well!
        Bots.show()
    }
    
    
    // So that you can recieve the notification even if the app is in the foreground
    func userNotificationCenter(_ center: UNUserNotificationCenter, willPresent notification: UNNotification, withCompletionHandler completionHandler: @escaping (UNNotificationPresentationOptions) -> Void) {
        completionHandler([.alert, .badge, .sound])
    }
    
    
}

