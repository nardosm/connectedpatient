//
//  Registration.swift
//  CVS
//
//  Created by Nardos Hailu on 4/6/18.
//  Copyright © 2018 Nardos Hailu. All rights reserved.
//

import Foundation
import UIKit
import SwiftSpinner
import SkyFloatingLabelTextField

class Registration: UIViewController,UITextFieldDelegate {
    
    
    @IBOutlet weak var firstName: SkyFloatingLabelTextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.hideKeyboardWhenTappedAround()
        firstName.delegate = self
        
        var firstNameRec:CGRect = firstName.frame
        firstNameRec.size.height = 30
        firstName.frame = firstNameRec
        
    }
    
    func textFieldDidBeginEditing(_ textField: UITextField) {
        moveTextFieldOnKeyboardInput(textField: textField as! SkyFloatingLabelTextField, moveDistance: -150, up: true)
    }
    
    func textFieldDidEndEditing(_ textField: UITextField) {
        moveTextFieldOnKeyboardInput(textField: textField as! SkyFloatingLabelTextField, moveDistance: -150, up: false)
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
    
    func moveTextFieldOnKeyboardInput(textField:SkyFloatingLabelTextField, moveDistance: Int, up:Bool ){
        
        let moveDuration = 0.3
        let movement: CGFloat = CGFloat (up ? moveDistance: -moveDistance)
        
        UIView.beginAnimations("animateTextField", context: nil)
        UIView.setAnimationBeginsFromCurrentState(true)
        UIView.setAnimationDuration(moveDuration)
        self.view.frame = self.view.frame.offsetBy(dx:0, dy:movement)
        UIView.commitAnimations()
    }
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func registrationButtonTapped(_ sender: Any) {
        SwiftSpinner.show(duration: 4.0, title: "Creating your user profile...")
        dismiss(animated: true, completion: nil)
    
        
    }
    
    @IBAction func closeButton(_ sender: Any) {
         dismiss(animated: true, completion: nil)
    }

}
