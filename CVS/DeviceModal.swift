//
//  DeviceModal.swift
//  CVS
//
//  Created by Nardos Hailu on 4/4/18.
//  Copyright © 2018 Nardos Hailu. All rights reserved.
//

import UIKit
import SafariServices

class DeviceModal: UIViewController {
    
    
    @IBOutlet weak var iHealthView: UIView!
    @IBOutlet weak var fitBitView: UIView!
    
    
    let urlString = "https://www.fitbit.com/oauth2/authorize?response_type=token&client_id=22CNGX&redirect_uri=http%3A%2F%2Fexample.com&scope=activity%20heartrate%20location%20nutrition%20profile%20settings%20sleep%20social%20weight&expires_in=604800"
    
    let iHealthURLString = "https://api.ihealthlabs.com:8443/OpenApiV2/OAuthv2/userauthorization/?client_id=0472d3fcfc0f405b93fc4d2626e3386f&response_type=code&redirect_uri=http://example.com&APIName=OpenApiBP&RequiredAPIName=OpenApiBG+OpenApiBP&IsNew=true"
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let gesture = UITapGestureRecognizer(target: self, action:  #selector (self.someAction (_:)))
         let gestureiHealth = UITapGestureRecognizer(target: self, action:  #selector (self.someActionIHealth (_:)))
        self.fitBitView.addGestureRecognizer(gesture)
        self.iHealthView.addGestureRecognizer(gestureiHealth)
        // Do any additional setup after loading the view.
    }
    
    @IBAction func dismissModal(_ sender: Any) {
        dismiss(animated: true, completion: nil)
    }
    
    @objc func someAction(_ sender:UITapGestureRecognizer){
        
        let svc = SFSafariViewController(url: URL(string: urlString)!)
        self.present(svc, animated:true, completion: nil)
        
    }
    
    @objc func someActionIHealth(_ sender:UITapGestureRecognizer){
        
        let svc = SFSafariViewController(url: URL(string: iHealthURLString)!)
        self.present(svc, animated:true, completion: nil)
        
    }

}
