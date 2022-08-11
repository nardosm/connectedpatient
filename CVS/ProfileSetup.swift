//
//  ProfileSetup.swift
//  CVS
//
//  Created by Nardos Hailu on 4/4/18.
//  Copyright © 2018 Nardos Hailu. All rights reserved.
//

import Foundation
import UIKit
import fluid_slider
import FoldingTabBar


class ProfileSetup: UIViewController {

    
    @IBOutlet weak var weightSlider: Slider!
    @IBOutlet weak var heightSlider: Slider!
    @IBOutlet weak var genderSwitchControl: UISegmentedControl!
    
    let defaults = UserDefaults.standard
    var weightSliderValue: Int!
    var heightSliderValue: Double!
    
    var mbe: OMCMobileBackend!;
    var auth: OMCAuthorization!;
    let appDelegate = UIApplication.shared.delegate as! AppDelegate
    
    override func viewDidLoad() {
         super.viewDidLoad()
        
        mbe = appDelegate.myMobileBackend()
        auth = mbe.authorization;
        print ("User authorized:  \(auth.authorized)")
        
        auth.getCurrentUser { (error, user) in
            print("USER FIRST NAME: \(String(describing: user?.firstName!))")
        }
        
        
        let labelTextAttributes: [NSAttributedStringKey : Any] = [.font: UIFont.systemFont(ofSize: 15, weight: .bold), .foregroundColor: UIColor.white]
        
        weightSlider.attributedTextForFraction = { fraction in
            let formatter = NumberFormatter()
            formatter.maximumIntegerDigits = 3
            formatter.maximumFractionDigits = 0

            let string = formatter.string(from: (fraction * 500) as NSNumber) ?? ""
            return NSAttributedString(string: string)
        
        }
        
        weightSlider.setMaximumLabelAttributedText(NSAttributedString(string:"0",attributes: labelTextAttributes))
        weightSlider.setMaximumLabelAttributedText(NSAttributedString(string: "500",attributes: labelTextAttributes))
        weightSlider.fraction = 0.5
        weightSlider.shadowOffset = CGSize(width: 0, height: 10)
        weightSlider.shadowBlur = 5
        weightSlider.shadowColor = UIColor(white: 0, alpha: 0.1)
        weightSlider.contentViewColor = UIColor(red: 78/255.0, green: 77/255.0, blue: 224/255.0, alpha: 1)
    
        weightSlider.valueViewColor = .white
        
        weightSlider.addTarget(self, action: #selector(weightSliderValueChanged), for: .valueChanged)
        
        
        heightSlider.attributedTextForFraction = { fraction in
            let formatter = NumberFormatter()
            formatter.maximumIntegerDigits = 3
            formatter.maximumFractionDigits = 1
            
            let string = formatter.string(from: (fraction * 8) as NSNumber) ?? ""
            return NSAttributedString(string: string)
            
        }
        
        heightSlider.setMaximumLabelAttributedText(NSAttributedString(string:"0",attributes: labelTextAttributes))
        heightSlider.setMaximumLabelAttributedText(NSAttributedString(string: "8",attributes: labelTextAttributes))
        heightSlider.fraction = 0.5
        heightSlider.shadowOffset = CGSize(width: 0, height: 10)
        heightSlider.shadowBlur = 5
        heightSlider.shadowColor = UIColor(white: 0, alpha: 0.1)
        heightSlider.contentViewColor = UIColor(red: 78/255.0, green: 77/255.0, blue: 224/255.0, alpha: 1)
        
        heightSlider.valueViewColor = .white
        
        heightSlider.addTarget(self, action: #selector(heightSliderValueChanged), for: .valueChanged)
 
    }
    
   
    @objc func weightSliderValueChanged(slider: Slider){
        weightSliderValue = Int(round(slider.fraction * 500))
        print("ATTRIBUTED TEXT: \(weightSliderValue!)")
       
        
    }
    
    @objc func heightSliderValueChanged(slider: Slider){
        var value = slider.fraction * 8
        heightSliderValue = Double(round(10*value)/10)
        print("ATTRIBUTED TEXT: \(heightSliderValue!)")
        
       
    }
    
    
    @IBAction func genderControlChanged(_ sender: Any) {
        
        switch genderSwitchControl.selectedSegmentIndex{
        
            case 0:
                //case for Male
                print("Selected Male")
            case 1:
                //case for female
                print("Selected Female")
            default:
                break
        }
    }
    
    
    @IBAction func handleContinueButtonTap(_ sender: Any) {
        /*
        let myTabBar = self.storyboard?.instantiateViewController(withIdentifier: "myTabBar") as! YALFoldingTabBarController
        
        let appDelegate = UIApplication.shared.delegate as! AppDelegate
        appDelegate.window?.rootViewController = myTabBar
        
        */
        //myTabBar
        
        if (weightSliderValue != nil && heightSliderValue != nil){
            print("DISAPPEARING VIEW: \(weightSliderValue!)")
            print("DISAPPEARING VIEW: \(heightSliderValue!)")
            
            defaults.set(weightSliderValue, forKey: "PatientWeight")
            defaults.set(heightSliderValue, forKey: "PatientHeight")
            defaults.synchronize()
            print("User Defautls synchronized")
        }
        
    }
    
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        
        guard let tabBarController = segue.destination as? YALFoldingTabBarController else { return }
        tabBarController.navigationItem.hidesBackButton = true
        
        let item1 = YALTabBarItem(itemImage: UIImage(named: "dashboard_icon"), leftItemImage: nil, rightItemImage: nil)
        let item2 = YALTabBarItem(itemImage: UIImage(named: "devices_icon"), leftItemImage: UIImage(named: "edit_icon"), rightItemImage: nil)
        tabBarController.leftBarItems = [item1, item2]
        
        
        let item3 = YALTabBarItem(itemImage: UIImage(named: "barcode_icon"), leftItemImage: nil,rightItemImage: nil)
        let item4 = YALTabBarItem(itemImage: UIImage(named: "notifications_icon"), leftItemImage: nil, rightItemImage: nil)
        tabBarController.rightBarItems = [item3, item4]
        
        
        tabBarController.centerButtonImage = UIImage(named:"menu_icon")!
        tabBarController.selectedIndex = 1  
        
        //customize tabBarView
        tabBarController.tabBarView.extraTabBarItemHeight = YALExtraTabBarItemsDefaultHeight;
        tabBarController.tabBarView.offsetForExtraTabBarItems = YALForExtraTabBarItemsDefaultOffset;
        //tabBarController.tabBarView.backgroundColor = UIColor(red: 94.0/255.0, green: 91.0/255.0, blue: 149.0/255.0, alpha: 1)
        
        tabBarController.tabBarView.tabBarColor = UIColor(red: 0.0/255.0, green: 0.0/255.0, blue: 100.0/255.0, alpha: 1)
        tabBarController.tabBarViewHeight = YALTabBarViewDefaultHeight;
        tabBarController.tabBarView.tabBarViewEdgeInsets = YALTabBarViewHDefaultEdgeInsets;
        tabBarController.tabBarView.tabBarItemsEdgeInsets = YALTabBarViewItemsDefaultEdgeInsets;
        tabBarController.tabBarView.dotColor = UIColor.white
        
        
        
    }
    
    
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillAppear(animated)
        self.navigationController?.setNavigationBarHidden(true, animated: animated)

    }
    
    
   
    
    


}
