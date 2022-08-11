//
//  DemoCell.swift
//  FoldingCell
//
//  Created by Alex K. on 25/12/15.
//  Copyright © 2015 Alex K. All rights reserved.
//

import FoldingCell
import UIKit
import Cosmos

class TableCell: FoldingCell {
    

    @IBOutlet weak var closeNumberLabel: UILabel!
    @IBOutlet weak var openNumberLabel: UILabel!
    
    @IBOutlet weak var storeName: UILabel!
    @IBOutlet weak var storeNameExpanded: UILabel!
    
    @IBOutlet weak var storeAddressFolded: UILabel!
    @IBOutlet weak var storeAddressExpanded: UILabel!
    
    @IBOutlet weak var openNowFolded: UILabel!
    @IBOutlet weak var openNowExapanded: UILabel!
    
    
    @IBOutlet weak var ratingFolded: CosmosView!
    @IBOutlet weak var ratingExpanded: CosmosView!
    
    func update(_ rating: Double) {
        ratingFolded.rating = rating
        ratingExpanded.rating = rating
    }
    
    var number: Int = 0 {
        didSet {
            closeNumberLabel.text = String(number)
            openNumberLabel.text = String(number)
            
            ratingFolded.settings.updateOnTouch = false
            ratingExpanded.settings.updateOnTouch = false
            
           
        }
    }
    
    override public func prepareForReuse() {
        // Ensures the reused cosmos view is as good as new
        ratingFolded.prepareForReuse()
        ratingExpanded.prepareForReuse()
    }
    override func awakeFromNib() {
        //foregroundView.layer.cornerRadius = 10
        //foregroundView.layer.masksToBounds = true
        super.awakeFromNib()
        
        ratingFolded.settings.fillMode = .half
        ratingExpanded.settings.fillMode = .half
    }
    
    override func animationDuration(_ itemIndex: NSInteger, type _: FoldingCell.AnimationType) -> TimeInterval {
        let durations = [0.26, 0.2, 0.2]
        return durations[itemIndex]
    }
    @IBAction func confirmActionTap(_ sender: Any) {
         print("tap")
    }
}

