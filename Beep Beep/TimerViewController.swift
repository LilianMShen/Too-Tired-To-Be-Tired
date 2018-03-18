//
//  TimerViewController.swift
//  Beep Beep
//
//  Created by Boop Noodle on 3/17/18.
//  Copyright © 2018 Lilian Shen. All rights reserved.
//

import UIKit
import AVFoundation
import AudioToolbox

class TimerViewController: UIViewController {
    
    func vibrate(){
        AudioServicesPlaySystemSound(SystemSoundID(1000))
        AudioServicesPlayAlertSound(kSystemSoundID_Vibrate)
    }
    
    
    var timer = Timer()
    
    var seconds = 30
    
    
    
    @IBOutlet weak var TimerLabel: UILabel!
    
    
    
    @IBOutlet weak var SliderOutlet: UISlider!
    @IBAction func Slider(_ sender: UISlider) {
        seconds = Int(sender.value)
        TimerLabel.text = String(seconds)
        
    }
    
    
    
    @IBOutlet weak var StartOutlet: UIButton!
    @IBAction func Start(_ sender: Any) {
        timer = Timer.scheduledTimer(timeInterval: 1, target: self, selector: #selector(TimerViewController.counter), userInfo: nil, repeats: true)
    }
    
    @objc func counter(){
        if(seconds > 0){
            TimerLabel.text = String(seconds - 1)
            seconds -= 1
            SliderOutlet.setValue(Float(seconds - 1), animated:true)
        }
        else{
            seconds = 0
            timer.invalidate()
            vibrate()
            createAlert(titleText: "Exercise time!", messageText:"30 seconds of jumping jacks, pronto!")
        }
    }
    
    

    
    
    @IBAction func WorkOutOne(_ sender: Any) {
        seconds = 60
        TimerLabel.text = String(seconds)
        SliderOutlet.setValue(60, animated:true)
    }
    @IBAction func WorkOutTwo(_ sender: Any) {
        seconds = 45
        TimerLabel.text = String(seconds)
        SliderOutlet.setValue(45, animated:true)
    }
    @IBAction func WorkOutThree(_ sender: Any) {
        seconds = 30
        TimerLabel.text = String(seconds)
        SliderOutlet.setValue(30, animated:true)
    }
    @IBAction func WorkOutFour(_ sender: Any) {
        seconds = 15
        TimerLabel.text = String(seconds)
        SliderOutlet.setValue(15, animated:true)
    }
    @IBAction func WorkOutFive(_ sender: Any) {
        seconds = 5
        TimerLabel.text = String(seconds)
        SliderOutlet.setValue(5, animated:true)
    }
    
    
    
    @IBOutlet weak var activeGif: UIImageView!
    
    
    
    //write a func with a parameter that takes in the exercise needed
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        activeGif.loadGif(name: "active corgo")
        // Do any additional setup after loading the view.
    }
    
    //override func viewDidAppear(_ animated: Bool) {}

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func createAlert(titleText: String, messageText: String){
        let alert = UIAlertController(title: titleText, message: messageText, preferredStyle: .alert)
        
        alert.addAction(UIAlertAction(title: "Done", style: .default, handler: { (action) in
            alert.dismiss(animated:true, completion: nil)
            }))
        self.present(alert, animated: true, completion: nil)
    }
    
    

}
