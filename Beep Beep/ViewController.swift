//
//  ViewController.swift
//  Beep Beep
//
//  Created by Boop Noodle on 3/17/18.
//  Copyright © 2018 Lilian Shen. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    

    @IBOutlet weak var Continue: UIButton!
    @IBOutlet weak var sleepyGif: UIImageView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        sleepyGif.loadGif(name: "sleepy corgo")
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
}

