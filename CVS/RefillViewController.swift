//
//  RefillViewController.swift
//  dopeAF
//
//  Created by Walid Nasim on 3/26/18.
//  Copyright © 2018 Walid Nasim. All rights reserved.
//

import UIKit
import AVFoundation
import GoogleMaps
import Foundation


class CameraView: UIView {
    
    override class var layerClass: AnyClass {
        get {
            return AVCaptureVideoPreviewLayer.self
        }
    }
    override var layer: AVCaptureVideoPreviewLayer {
        get {
            return super.layer as! AVCaptureVideoPreviewLayer
        }
    }
}

class RefillViewController: UIViewController, AVCaptureMetadataOutputObjectsDelegate {
    //    private let locationManager = CLLocationManager()
    //    private let dataProvider = GoogleDataProvider()
    //    private let searchRadius: Double = 1000
    
    
    // Camera view
    var cameraView: CameraView!
    // AV capture session and dispatch queue
    let session = AVCaptureSession()
    let sessionQueue = DispatchQueue(label: AVCaptureSession.self.description(), attributes: [], target: nil)
    
    override func loadView() {
        cameraView = CameraView()
        view = cameraView
    }
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        session.beginConfiguration()
        //Location Manager
        //        locationManager.delegate = self
        //        locationManager.requestWhenInUseAuthorization()
        
        
        let videoDevice = AVCaptureDevice.default(for: AVMediaType.video)
        
        if (videoDevice != nil) {
            let videoDeviceInput = try? AVCaptureDeviceInput(device: videoDevice!)
            
            if (videoDeviceInput != nil) {
                if (session.canAddInput(videoDeviceInput!)) {
                    session.addInput(videoDeviceInput!)
                }
            }
            
            let metadataOutput = AVCaptureMetadataOutput()
            
            if (session.canAddOutput(metadataOutput)) {
                session.addOutput(metadataOutput)
                
                metadataOutput.metadataObjectTypes = [AVMetadataObject.ObjectType.ean13, AVMetadataObject.ObjectType.qr]
                
                metadataOutput.setMetadataObjectsDelegate(self as? AVCaptureMetadataOutputObjectsDelegate, queue: DispatchQueue.main)
            }
        }
        
        session.commitConfiguration()
        
        cameraView.layer.session = session
        cameraView.layer.videoGravity = .resizeAspectFill
        // Set initial camera orientation
        let videoOrientation: AVCaptureVideoOrientation
        switch UIApplication.shared.statusBarOrientation {
        case .portrait:
            videoOrientation = .portrait
        case .portraitUpsideDown:
            videoOrientation = .portraitUpsideDown
        case .landscapeLeft:
            videoOrientation = .landscapeLeft
        case .landscapeRight:
            videoOrientation = .landscapeRight
        default:
            videoOrientation = .portrait
        }
        cameraView.layer.connection?.videoOrientation = videoOrientation
        
    }
    
    var userCoordinates = [Double]()
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        // Hide NavBar
        navigationController?.setNavigationBarHidden(true, animated: false)
        
        // Start AV capture session
        sessionQueue.async {
            self.session.startRunning()
        }
    }
    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        
        //Show NavBat
        navigationController?.setNavigationBarHidden(false, animated: false)
        
        // Stop AV capture session
        sessionQueue.async {
            self.session.stopRunning()
        }
    }
    override func viewWillTransition(to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator) {
        super.viewWillTransition(to: size, with: coordinator)
        // Update camera orientation
        let videoOrientation: AVCaptureVideoOrientation
        switch UIDevice.current.orientation {
        case .portrait:
            videoOrientation = .portrait
        case .portraitUpsideDown:
            videoOrientation = .portraitUpsideDown
        case .landscapeLeft:
            videoOrientation = .landscapeRight
        case .landscapeRight:
            videoOrientation = .landscapeLeft
        default:
            videoOrientation = .portrait
        }
        cameraView.layer.connection?.videoOrientation = videoOrientation
    }
    func metadataOutput(_ output: AVCaptureMetadataOutput, didOutput metadataObjects: [AVMetadataObject], from connection: AVCaptureConnection) {
        if (metadataObjects.count > 0 && metadataObjects.first is AVMetadataMachineReadableCodeObject) {
            let scan = metadataObjects.first as! AVMetadataMachineReadableCodeObject
            
            //            let alertController = UIAlertController(title: "Barcode Scanned", message: scan.stringValue, preferredStyle: .alert)
            let alertController = UIAlertController(title: "Barcode Scanned", message: "Would you like to refill your prescription of Xarelto?", preferredStyle: .alert)
            
            alertController.addAction(UIAlertAction(title: "Refill", style: .default, handler: { action in
                
                //                let url = URL(string: "https://maps.googleapis.com/maps/api/place/nearbysearch/json?location=38.8793682586764,-77.2291971278165&radius=500&keyword=cvspharmacy&key=AIzaSyClGYMRRfHVZZXBNHic0-TeGIHgo7W_Qto")!
                //                let urlSession = URLSession.shared
                //                let getRequest = URLRequest(url: url)
                //                let task = urlSession.dataTask(with: getRequest as URLRequest, completionHandler: { data, response, error in
                //
                //                    guard error == nil else {
                //                        return
                //                    }
                //
                //                    guard let data = data else {
                //                        return
                //                    }
                //
                //                    do {
                //
                //                        // the data is returned in JSON format and needs to be converted into something that swift can work with
                //                        // we are converting it into a dictionary of type [String: Any]
                //                        if let json = try JSONSerialization.jsonObject(with: data, options: .mutableContainers) as? [String: Any] {
                //                            print("success!")
                //                            print(json["results"])
                ////                            for (index,element) in json["results"].enumerated(){
                ////                                print(index)
                ////                            }
                //                        }
                //                    } catch let error {
                //                        print(error.localizedDescription)
                //                    }
                //                })
                //
                //                task.resume()
                
                
                
                
                self.performSegue(withIdentifier: "locationSegue", sender: self)
                //
                
                
                
            }))
            alertController.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler:nil))
            
            if self.presentedViewController == nil {
                self.present(alertController, animated: true, completion: nil)
            }
            
            //            present(alertController, animated: true, completion: nil)
        }
    }
    
}

//extension RefillViewController: CLLocationManagerDelegate {
//    // 2
//    func locationManager(_ manager: CLLocationManager, didChangeAuthorization status: CLAuthorizationStatus) {
//        // 3
//        guard status == .authorizedWhenInUse else {
//            return
//        }
//        // 4
//        locationManager.startUpdatingLocation()
//    }
//
//    // 6
//    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
//        guard let location = locations.first else {
//            return
//        }
//
//        // 7
//
//        print("coordinate \(location.coordinate)")
//
//
//
//
//
//
//        // 8
//        locationManager.stopUpdatingLocation()
//
//    }
//}

