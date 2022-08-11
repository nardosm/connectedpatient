//
//  ManageNotifications.swift
//  CVS
//
//  Created by Nardos Hailu on 4/4/18.
//  Copyright © 2018 Nardos Hailu. All rights reserved.
//

import Foundation
import UIKit
import SwiftSpinner
import UserNotifications
import Bots

class ManageNotifications: UIViewController {

    var mbe: OMCMobileBackend!;
    
    var auth: OMCAuthorization!;
    var storage: OMCStorage!
    var client:OMCCustomCodeClient!
    
    @IBOutlet weak var fitbitTime: UIDatePicker!
    @IBOutlet weak var ihealthTime: UIDatePicker!
    @IBOutlet weak var pillboxTime: UIDatePicker!
    
    var jobSchedulePOSTURL = "/mobile/custom/cvsdatacheck/updateScheduleCheckTime"
    var jobScheduleGETURL = "/mobile/custom/cvsdatacheck/scheduleJob"
    let appDelegate = UIApplication.shared.delegate as! AppDelegate
    
    override func viewDidLoad() {
        super.viewDidLoad()
 
        mbe = appDelegate.myMobileBackend()
        auth = mbe.authorization;
        client = mbe.customCodeClient
        
        //getNotificationSettings()
       
        

    }
    
    
    
    @IBAction func saveButtonTapped(_ sender: Any) {
       // setNotificationSettings()
        
    
        SwiftSpinner.show("Saving your preferences...")
        
       
        // Add local notification to trigger a few seconds after butting is tapped to demonstrate example reminder
        let content = UNMutableNotificationContent()
        content.title = "REMINDER"
        content.body = "You have missed your medication for today!"
        content.sound = UNNotificationSound.default()
        
        let trigger = UNTimeIntervalNotificationTrigger(timeInterval: 6, repeats: false)
        
        let request = UNNotificationRequest(identifier: "NurseBot", content: content, trigger: trigger)
        
        UNUserNotificationCenter.current().add(request, withCompletionHandler: nil)
        
        
        // show the SwiftSpinner for only 3 seconds!
        DispatchQueue.main.asyncAfter(deadline: .now() + 3.0, execute: {
            self.hideSpinner()
        })
        
        
    }
    
    func hideSpinner(){
        SwiftSpinner.hide()
    }
    
    // Remove all remote notification stuff
    /*
    func setNotificationSettings(){
        
        SwiftSpinner.show("Setting your preferences...")
        
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "HHmm"
        let userSetTimeFitbit = dateFormatter.string(from: fitbitTime.date)
        let userSetTimeBloodPress = dateFormatter.string(from: ihealthTime.date)
        print("FITBIT TIMEEEE: \(userSetTimeFitbit)")
        
        
        let jsonObject: [String: Any] =
            [
                "bloodPressureCheckTime": Int(userSetTimeFitbit) as Any,
                "fitbitCheckTime": Int(userSetTimeBloodPress) as Any,
                "pillboxCheckTime": Int(userSetTimeFitbit) as Any
        ]
        
        if JSONSerialization.isValidJSONObject(jsonObject) {
            if let data = try? JSONSerialization.data(withJSONObject: jsonObject, options: []) {
                
                print("JSON data object is:\(data)")
                client.invokeCustomRequest(jobSchedulePOSTURL, method: "POST", data: data) { (error, response, responseData) in
                    
                    
                    if (error == nil){
                        print("JSON data object is:\(String(describing: responseData))")
                        //SwiftSpinner.show("Your preferences have been saved!", animated: false)
                        
                        sleep(3)
                        SwiftSpinner.hide()
                    }
                    else{
                        print(error as Any)
                        SwiftSpinner.show("Failed to connect, waiting...", animated: false)
                    }
                    
                    
                }
                
            }
        }
    }
    */
    
    /*
    func getNotificationSettings(){
     
        SwiftSpinner.show("Fetching your settings...")
        client.invokeCustomRequest(jobScheduleGETURL, method: "GET", data: nil) { (error, response, responseData) in
            
            if (error == nil){
                print("JSON data object is:\(String(describing: responseData))")
                if let dictionary = responseData as? [String: Any] {
                    if let bloodPressureNextCheck = dictionary["BloodPressureNextCheckDateTime"] as? String,
                        let fitbitNextCheck = dictionary["FitbitNextCheckDateTime"] as? String
                        {
                        print("Date Value is :\(String(describing: bloodPressureNextCheck))")
                        
                        // create dateFormatter with UTC time format
                        let dateFormatter = DateFormatter()
                        dateFormatter.dateFormat = "yyyy-MM-dd'T'HH:mm:ss.SSSXXXXX"
                        dateFormatter.timeZone = TimeZone(abbreviation:"UTC")
                        let bloodPressureDate = dateFormatter.date(from: bloodPressureNextCheck)
                        let fitbitDate = dateFormatter.date(from: fitbitNextCheck)
                            print("FOUND DATE IS: \(String(describing: bloodPressureDate))")
                        // change to a readable time format and change to local time zone
                        dateFormatter.dateFormat = "HH:mm"
                        dateFormatter.timeZone = TimeZone.current
                       
                        let bloodPressureSyncTime = dateFormatter.string(from: bloodPressureDate!)
                        let fitbitSyncTime = dateFormatter.string(from: fitbitDate!)
                        print("NEXT SYNC TIME is :\(String(describing: bloodPressureSyncTime))")
                        
                        self.fitbitTime.date = dateFormatter.date(from: fitbitSyncTime)!
                        self.ihealthTime.date = dateFormatter.date(from: bloodPressureSyncTime)!
                        self.pillboxTime.date = dateFormatter.date(from: fitbitSyncTime)!
                            
                        SwiftSpinner.hide()
                    }
                }
 
            }
            else{
                print(error as Any)
            }
 
 
        }
 
    
        
    } */

}

