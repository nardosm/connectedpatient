//
//  AppDelegate.swift
//  CVS
//
//  Created by Nardos Hailu on 4/3/18.
//  Copyright © 2018 Nardos Hailu. All rights reserved.
//

import UIKit
import FoldingTabBar
import UserNotifications
import Bots

let OMC_MBE_Name:String = "MyMobileBackend"
fileprivate var mbe: OMCMobileBackend!;

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate, UNUserNotificationCenterDelegate {

    var window: UIWindow?
    var deviceTokenData: Data?


    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.
        
        //loginStoryBoard
        
        UNUserNotificationCenter.current().delegate = self
        
        
        setupYALTabBarController()
        
        let center = UNUserNotificationCenter.current()
        center.requestAuthorization(options:[.badge, .alert, .sound]) { (granted, error) in
            print("Notification authorization granted by the user")
        }
        //this code should trigger 'didRegisterForRemoteNotificationsWithDeviceToken' below if registration is successful
        application.registerForRemoteNotifications()
        
        Thread.sleep(forTimeInterval: 0.8)
        return true
    }
    
    // So that you can recieve the notification even if the app is in the foreground
    func userNotificationCenter(_ center: UNUserNotificationCenter, willPresent notification: UNNotification, withCompletionHandler completionHandler: @escaping (UNNotificationPresentationOptions) -> Void) {
        completionHandler([.alert, .badge, .sound])
    }
    
    // Directing to the app once the notification is tapped!
    func userNotificationCenter(_ center: UNUserNotificationCenter, didReceive response: UNNotificationResponse, withCompletionHandler completionHandler: @escaping () -> Void) {
        
        if response.notification.request.identifier == "NurseBot"{
            print("handling w/ id")
            
            // Initialize Med Bot (old: 5bfc13448eeb450022e3d7ef)
            Bots.initWith(OMCSettings(appId: "5c34cc1d5c3ec30022018153")) { (error: Error?, userInfo: [AnyHashable : Any]?) in
                print("Bot initialized")
                Bots.setUserFirstName("John", lastName: "Dunbar")
                Bots.conversation()?.sendMessage(OMCMessage.init(text: "Session Began: "))
                
            }
            
            Bots.show()
        }
        
        completionHandler()
    }
    
    func myMobileBackend() -> OMCMobileBackend? {
        
        let mobileManager: OMCMobileManager = OMCMobileManager.shared()
        
         if (  mobileManager.mobileBackend != nil ) {
            mbe =  mobileManager.mobileBackend;
            if ( mbe != nil ) {
                print("Mobile backend configured for Base URL %@",mbe.baseURL ?? "");
                return mbe;
            }
         }
        NSLog("Mobile backend configuration failed");
        return nil;
    }
    func application(_ application: UIApplication, didRegisterForRemoteNotificationsWithDeviceToken deviceToken: Data) {
       /* print("WE ARE INSIDE THE TOKEN REGISTRATION")
        let tokenParts = deviceToken.map { data -> String in
            return String(format: "%02.2hhx", data)
        }
        let token = tokenParts.joined()
        print("DEVICE TOKEN: ", token)
        
        
        let notifications = myMobileBackend()?.notifications()
        let deviceTokenData:Data! = deviceToken.base64EncodedData()
        notifications?.register(forNotifications: deviceTokenData as Data!, onSuccess: { (response:HTTPURLResponse!) in
            print("Device token registered successfully on MCS server");
        })
          
        { (error) in
            print("Error: %@", error?.localizedDescription);
        };
        */
        
        deviceTokenData = deviceToken
        let deviceTokenString = deviceToken.reduce("", {$0 + String(format: "%02X", $1)})
        print("My Device token is + \(deviceTokenString)")
        
    }

    func applicationWillResignActive(_ application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
    }

    func applicationDidEnterBackground(_ application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }

    func applicationWillEnterForeground(_ application: UIApplication) {
        // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
    }

    func applicationDidBecomeActive(_ application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }

    func applicationWillTerminate(_ application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }
}

private extension AppDelegate {
    
    func setupYALTabBarController() {
        
        
        
        
        
//        guard let tabBarController = window?.rootViewController as? YALFoldingTabBarController else { return }
//        
//        let item1 = YALTabBarItem(itemImage: UIImage(named: "nearby_icon"), leftItemImage: nil, rightItemImage: nil)
//        let item2 = YALTabBarItem(itemImage: UIImage(named: "nearby_icon"), leftItemImage: UIImage(named: "edit_icon"), rightItemImage: nil)
//        tabBarController.leftBarItems = [item1, item2]
//        
//        
//        let item3 = YALTabBarItem(itemImage: UIImage(named: "new_chat_icon"), leftItemImage: nil,rightItemImage: nil)
//        let item4 = YALTabBarItem(itemImage: UIImage(named: "new_chat_icon"), leftItemImage: nil, rightItemImage: nil)
//        tabBarController.rightBarItems = [item3, item4]
//
//        
//        tabBarController.centerButtonImage = UIImage(named:"menu_icon")!
//        tabBarController.selectedIndex = 0
//        
//        //customize tabBarView
//        tabBarController.tabBarView.extraTabBarItemHeight = YALExtraTabBarItemsDefaultHeight;
//        tabBarController.tabBarView.offsetForExtraTabBarItems = YALForExtraTabBarItemsDefaultOffset;
//        //tabBarController.tabBarView.backgroundColor = UIColor(red: 94.0/255.0, green: 91.0/255.0, blue: 149.0/255.0, alpha: 1)
//        
//        tabBarController.tabBarView.tabBarColor = UIColor(red: 0.0/255.0, green: 0.0/255.0, blue: 100.0/255.0, alpha: 1)
//        tabBarController.tabBarViewHeight = YALTabBarViewDefaultHeight;
//        tabBarController.tabBarView.tabBarViewEdgeInsets = YALTabBarViewHDefaultEdgeInsets;
//        tabBarController.tabBarView.tabBarItemsEdgeInsets = YALTabBarViewItemsDefaultEdgeInsets;
//        tabBarController.tabBarView.dotColor = UIColor.white
    }
}

