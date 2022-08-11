

import FoldingCell
import UIKit
import GoogleMaps
import Foundation
import SwiftyJSON
import SwiftSpinner
import Alamofire

class MainTableViewController: UITableViewController {
    
    let kCloseCellHeight: CGFloat = 110
    let kOpenCellHeight: CGFloat = 292
    let kRowsCount = 10
    var cellHeights: [CGFloat] = []
    

    @IBOutlet var storesTableView: UITableView!
    
    
    private let locationManager = CLLocationManager()
    private let searchRadius: Double = 1000
    
    var stores: [[String: AnyObject]] = [[String:AnyObject]]()
    var userCoordinates = [Double]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        locationManager.requestWhenInUseAuthorization()
        locationManager.delegate = self as! CLLocationManagerDelegate
        SwiftSpinner.show(duration: 4.0, title:"Finding nearest AVS Pharmacies...")
        setup()
        
       
        
        
    }
    
    private func setup() {
        cellHeights = Array(repeating: kCloseCellHeight, count: kRowsCount)
        tableView.estimatedRowHeight = kCloseCellHeight
        tableView.rowHeight = UITableViewAutomaticDimension
        tableView.backgroundColor = UIColor.white
    }
}

// MARK: - TableView

extension MainTableViewController {
    
    override func tableView(_: UITableView, numberOfRowsInSection _: Int) -> Int {
        return stores.count
    }
    
    override func tableView(_: UITableView, willDisplay cell: UITableViewCell, forRowAt indexPath: IndexPath) {
        guard case let cell as TableCell = cell else {
            return
        }
        
        cell.backgroundColor = .clear
        
        if cellHeights[indexPath.row] == kCloseCellHeight {
            cell.unfold(false, animated: false, completion: nil)
        } else {
            cell.unfold(true, animated: false, completion: nil)
        }
        
        cell.number = indexPath.row + 1
        print("INDEX ROW: \(indexPath.row)")
        if (self.stores.count > 0){
            
            print("INDEX ROW: \(indexPath.row)")
            let store = self.stores[indexPath.row]
            cell.storeAddressFolded.text = (store["vicinity"] as! String)
            cell.storeAddressExpanded.text = (store["vicinity"] as! String)
            
            //cell.storeName.text = (store["name"] as! String)
            cell.storeName.text = "AVS"
            //cell.storeNameExpanded.text = (store["name"] as! String)
            cell.storeNameExpanded.text = "AVS"
            
            if (store["opening_hours"]!["open_now"] as! Bool){
                cell.openNowFolded.text = "Yes"
                cell.openNowExapanded.text = "Yes"
            }
            else{
                cell.openNowFolded.text = "No"
                cell.openNowExapanded.text = "No"
            }
            
            cell.update(store["rating"]! as! Double)
            
            print (store["opening_hours"]!["open_now"] as! Bool)
        }
        
        
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "cell", for: indexPath) as! FoldingCell
        let durations: [TimeInterval] = [0.26, 0.2, 0.2]
        cell.durationsForExpandedState = durations
        cell.durationsForCollapsedState = durations
        
        return cell
    }
    
    override func tableView(_: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return cellHeights[indexPath.row]
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
        let cell = tableView.cellForRow(at: indexPath) as! FoldingCell
        
        if cell.isAnimating() {
            return
        }
        
        var duration = 0.0
        let cellIsCollapsed = cellHeights[indexPath.row] == kCloseCellHeight
        if cellIsCollapsed {
            cellHeights[indexPath.row] = kOpenCellHeight
            cell.unfold(true, animated: true, completion: nil)
            duration = 0.5
        } else {
            cellHeights[indexPath.row] = kCloseCellHeight
            cell.unfold(false, animated: true, completion: nil)
            duration = 0.8
        }
        
        UIView.animate(withDuration: duration, delay: 0, options: .curveEaseOut, animations: { () -> Void in
            tableView.beginUpdates()
            tableView.endUpdates()
        }, completion: nil)
    }
}

extension MainTableViewController: CLLocationManagerDelegate {
    // 2
    func locationManager(_ manager: CLLocationManager, didChangeAuthorization status: CLAuthorizationStatus) {
        // 3
        guard status == .authorizedWhenInUse else {
            return
        }
        // 4
        self.locationManager.startUpdatingLocation()
        
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
                    print(responseResults)
                    self.stores = responseResults as [[String : AnyObject]]
                    self.storesTableView.reloadData()
                }
            }
        }
        
        DispatchQueue.main.asyncAfter(deadline: .now() + 2){ // change 2 to desired number of seconds
            //            // Your code with delay
            SwiftSpinner.hide()
        }
        
        
        
        
        
        // 8
        locationManager.stopUpdatingLocation()
        
    }
}

