//
//  LocationsViewController.swift
//  dopeAF
//
//  Created by Walid Nasim on 4/5/18.
//  Copyright © 2018 Walid Nasim. All rights reserved.
//

import UIKit
import GoogleMaps
import Foundation
import SwiftyJSON
import SwiftSpinner
import Alamofire
import AlamofireImage

class LocationsViewController: UIViewController, UITableViewDelegate, UITableViewDataSource {
    
    
    private let locationManager = CLLocationManager()
    //    private let dataProvider = GoogleDataProvider()
    private let searchRadius: Double = 1000
    
    @IBOutlet weak var table1: UITableView!
    //    var coordinates = [CLLocationCoordinate2D]()

    var stores: [[String: AnyObject]] = [[String:AnyObject]]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        table1.delegate = self
        table1.dataSource = self
        
        locationManager.delegate = self
        locationManager.requestWhenInUseAuthorization()
        
        SwiftSpinner.show("Finding nearest AVS Pharmacies...")
    }
    
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return stores.count
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell: CustomTableViewCell = tableView.dequeueReusableCell(withIdentifier: "cell") as! CustomTableViewCell!
        
        if self.stores.count > 0{
            let store = self.stores[indexPath.row]
            //cell.storeAddress?.text = (store["vicinity"] as! String)
            print (store["vicinity"] as! String)
        }
 
        return cell
    }
    
    var userCoordinates = [Double]()
    
    
}



extension LocationsViewController: CLLocationManagerDelegate {
    // 2
    func locationManager(_ manager: CLLocationManager, didChangeAuthorization status: CLAuthorizationStatus) {
        // 3
        guard status == .authorizedWhenInUse else {
            return
        }
        // 4
        locationManager.startUpdatingLocation()
    }
    
    // 6
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        guard let location = locations.first else {
            return
        }
        manager.stopUpdatingLocation()
        manager.delegate = nil
        
        // 7
        
        
        print("coordinate \(location.coordinate)")
        let url = URL(string: "https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=\(location.coordinate.latitude),\(location.coordinate.longitude)&radius=5000&keyword=cvspharmacy&key=AIzaSyClGYMRRfHVZZXBNHic0-TeGIHgo7W_Qto")!
        self.locationManager.stopUpdatingLocation()
        
        Alamofire.request(url).responseJSON { (response) in
            if let responseValue = response.result.value as? [String:AnyObject]{
                if let responseResults = responseValue["results"] as! [[String: Any]]?{
                    //print(responseResults)
                    self.stores = responseResults as [[String : AnyObject]]
                    self.table1.reloadData()
                }
            }
        }

        DispatchQueue.main.async{ // change 2 to desired number of seconds
            //            // Your code with delay
            SwiftSpinner.hide()
        }
        
        
        
        
        
        // 8
        locationManager.stopUpdatingLocation()
        
    }
}
