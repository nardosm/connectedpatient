//
//  Login.swift
//  CVS
//
//  Created by Nardos Hailu on 4/3/18.
//  Copyright © 2018 Nardos Hailu. All rights reserved.
//

import Foundation
import UIKit
import SkyFloatingLabelTextField
import SwiftSpinner
import Security
import LocalAuthentication

class Login: UIViewController,UITextFieldDelegate {
    
    @IBOutlet weak var textField: SkyFloatingLabelTextField!
    @IBOutlet weak var passwordField: SkyFloatingLabelTextField!
    
    var mbe: OMCMobileBackend!;
    var auth: OMCAuthorization!;

    
     let appDelegate = UIApplication.shared.delegate as! AppDelegate
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        
        self.hideKeyboardWhenTappedAround()
        
        //authenticateUser()
        mbe = appDelegate.myMobileBackend()
        auth = mbe.authorization;
     
        //print ("User authorized:  \(auth.authorized)")
       
        /*
         //This is to read passsword item from the keychain that's set previously
        do {
            let passwordItem = KeychainPasswordItem(service: KeychainConfiguration.serviceName, account: accountName, accessGroup: KeychainConfiguration.accessGroup)
            
            accountNameField.text = passwordItem.account
            passwordField.text = try passwordItem.readPassword()
        }
        catch {
            fatalError("Error reading password from keychain - \(error)")
        }
        */
        
        textField.delegate = self
        passwordField.delegate = self
        
        var textFieldRect:CGRect = textField.frame
        textFieldRect.size.height = 50
        textField.frame = textFieldRect
        
        var passwordFieldRect:CGRect = passwordField.frame
        passwordFieldRect.size.height = 50
        passwordField.frame = passwordFieldRect
    }
    
    func textFieldDidBeginEditing(_ textField: UITextField) {
        moveTextFieldOnKeyboardInput(textField: textField as! SkyFloatingLabelTextField, moveDistance: -80, up: true)
    }
    
    func textFieldDidEndEditing(_ textField: UITextField) {
        moveTextFieldOnKeyboardInput(textField: textField as! SkyFloatingLabelTextField, moveDistance: -80, up: false)
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
    
    
    @IBAction func loginButtonTapped(_ sender: Any) {
        
        performLogin(username: textField.text!, password: passwordField.text!)
        
    }
    
    func authenticateUser() {
        let context = LAContext()
        var error: NSError?
        
        if context.canEvaluatePolicy(.deviceOwnerAuthenticationWithBiometrics, error: &error) {
            let reason = "Identify yourself!"
            
            context.evaluatePolicy(.deviceOwnerAuthenticationWithBiometrics, localizedReason: reason) {
                [unowned self] success, authenticationError in
                
                DispatchQueue.main.async {
                    if success {
                        print ("FACE ID SUCCESS!!!!")
                        
                        //self.performLogin(username: "annadil.zaman@oracle.com",password: "Annaz#$%0000")
                        self.performSegue(withIdentifier: "logintouserprofile", sender: self)
                        
                        
                    } else {
                        //let ac = UIAlertController(title: "Authentication failed", message: "Sorry!", preferredStyle: .alert)
                        //ac.addAction(UIAlertAction(title: "OK", style: .default))
                        //self.present(ac, animated: true)
                    }
                }
            }
        } else {
            let ac = UIAlertController(title: "Touch ID not available", message: "Your device is not configured for Touch ID.", preferredStyle: .alert)
            ac.addAction(UIAlertAction(title: "OK", style: .default))
            present(ac, animated: true)
        }
    }
    
    @IBAction func faceIDTapped(_ sender: Any) {
        authenticateUser()
    }
    
    
    func performLogin(username: String, password: String){
        
       
        SwiftSpinner.show("Logging you in...")
        
        if ( mbe == nil ) {
           
            SwiftSpinner.hide()
            let alert = UIAlertController(title: "Error", message:"No matching mobile backend found in OMC.plist", preferredStyle: UIAlertControllerStyle.alert)
            alert.addAction(UIAlertAction(title: "OK", style: UIAlertActionStyle.default, handler: nil))
            self.present(alert, animated: true, completion: nil)
            
        }
        else{
                        
            let error: NSError? = auth.authenticate(username, password: password) as NSError?
            
    
            if (error == nil) {
                
                /*
                 //This is code to save our username and password to keychain!
                 do{
                 let passwordItem = KeychainPasswordItem(service: "CVSAPP", account: "nardos.megersa@oracle.com",accessGroup: nil)
                 try passwordItem.savePassword("")
                 }
                 catch{
                 fatalError("Error updating keychain - \(error)")
                 }
                 */
                
                performSegue(withIdentifier: "logintouserprofile", sender: nil)
                SwiftSpinner.hide()
            }
            else {
               
                SwiftSpinner.hide()
                print ("Error: \(error!.localizedDescription)")
                let alert = UIAlertController(title: "Error!!!!!", message:error!.localizedDescription, preferredStyle: UIAlertControllerStyle.alert)
                alert.addAction(UIAlertAction(title: "OK", style: UIAlertActionStyle.default, handler: nil))
                self.present(alert, animated: true, completion: nil)
                
                
            }
        }
    }
    
    
    
}
