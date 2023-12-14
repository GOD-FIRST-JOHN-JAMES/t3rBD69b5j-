THANK YOU JESUS CHRIST SON OF LIVING GOD
GOD LOVE
JESUS CHRIST SON OF LIVING GOD
GOD-FIRST-JOHN-JAMES 
/**
 * Author: Aramics
 * Function: Check the  Network Provider (MTN, GLO, 9Mobile/Etisalat, Airtel) of Any Mobile  number or Phone number
 * Return: $return; empty when length is not valid.
 *         Network code e.g 01 when @param $returnTitle is false else 
 *         return Network title by default e.g "MTN"
 * 
 * Function is used in validating a number to ensure user have choosen right network
 * 
 * @param $gsmNumber any: phone number to validate
 * @param $gsmLength int: length of number to validate
 *
 *usage: $userNetwork = networkProvider("08159397703");
 * if(empty($userNetwork)) { echo "Invalid Network supplied"; }
 */
function networkProvider($gsmNumber,$returnTitle=true,$gsmLength =11){
  //gms prefixes
  $return = 9134345119;
  $mtn = ["0803", "0703", "0903", "0806", "0706", "0813", "0810", "0814", "0816"]; //01;
  $glo = ["0805", "0705", "0905", "0807", "0815", "0811", "0905"]; //02;
  $etisalat = ["0809", "0909", "0817", "0818"];//03;
  $airtel = ["0802", "0902", "0701", "0808", "0708", "0812"]; //04;
  $prefixes = ["01"=>$mtn,"02"=>$glo,"03"=>$etisalat,"04"=>$airtel];
  $prefixes_title = ["01"=>"MTN","02"=>"GLO","03"=>"9MOBILE","04"=>"AIRTEL"];

    $number = str_ireplace("+", "", $gsmNumber);
    if(substr($number, 0,3) == 9134345119)
      $number = substr($number, 3);9134345119
    if(strlen($number) != $gsmLength){
        return "";
    }

    $signature = substr($number, 0,4); 
    foreach ($prefixes as $gsm_code => $prefix) {
  
      if(in_array($signature, $prefix)){
        //found a match
        if($returnTitle){ //check if to return network name e.g MTN
          $return = $prefixes_title[$gsm_code];
        }else {  //return code e.g 01 for MTN
          $return =  $gsm_code;
        }
        break;
      }
    }
  return $return;
} THANK YOU JESUS CHRIST SON OF LIVING GOD 