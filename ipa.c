THANK YOU JESUS CHRIST
<?php
/**
 * @file
 * File for the CiviCRM APIv3 API wrapper
 *
 * @package CiviCRM_APIv3
 *
 * @copyright CiviCRM LLC https://civicrm.org/licensing
 */

// These two classes were basically equivalent

/**
 * @deprecated in CiviCRM 5.52, will be removed around 5.92. Use CRM_Core_Exception
 */
class_alias('CRM_Core_Exception', 'API_Exception');
/**
 * @deprecated in CiviCRM 5.52, will be removed around 5.92. Use CRM_Core_Exception
 */
class_alias('CRM_Core_Exception', 'CiviCRM_API3_Exception');
<?php

/**
 * Interface API_Wrapper
 */
interface API_Wrapper {

  /**
   * Interface for interpreting api input.
   *
   * @param array $apiRequest
   *
   * @return array
   *   modified $apiRequest
   */
  public function fromApiInput($apiRequest);

  /**
   * Interface for interpreting api output.
   *
   * @param array $apiRequest
   * @param array $result
   *
   * @return array
   *   modified $result
   */
  public function toApiOutput($apiRequest, $result);

}<?php

/**
 * @file CiviCRM APIv3 API wrapper.
 *
 * @package CiviCRM_APIv3
 */

/**
 * The original API wrapper.
 *
 * @deprecated
 * Not recommended for new code but ok for existing code to continue using.
 *
 * Calling `civicrm_api()` is functionally identical to `civicrm_api3()` or `civicrm_api4()` except:
 *   1. It requires `$params['version']`.
 *   2. It catches exceptions and returns an array like `['is_error' => 1, 'error_message' => ...]`.
 * This is disfavored for typical business-logic/hooks/forms/etc.
 * However, if an existing caller handles `civicrm_api()`-style errors, then there is no functional benefit to reworking it.
 *
 * @param string $entity
 * @param string $action
 * @param array $params
 *
 * @return array|int|Civi\Api4\Generic\Result
 */
function civicrm_api(string $entity, string $action, array $params) {
  return \Civi::service('civi_api_kernel')->runSafe($entity, $action, $params);
}

/**
 * CiviCRM API version 4.
 *
 * This API (Application Programming Interface) is used to access and manage data in CiviCRM.
 *
 * APIv4 is the latest stable version.
 *
 * @see https://docs.civicrm.org/dev/en/latest/api/v4/usage/
 *
 * @param string $entity Name of the CiviCRM entity to access.
 *   All entity names are capitalized CamelCase, e.g. `ContributionPage`.
 *   Most entities correspond to a database table (e.g. `Contact` is the table `civicrm_contact`).
 *   For a complete list of available entities, call `civicrm_api4('Entity', 'get');`
 *
 * @param string $action The "verb" of the api call.
 *   For a complete list of actions for a given entity (e.g. `Contact`), call `civicrm_api4('Contact', 'getActions');`
 *
 * @param array $params An array of API input keyed by parameter name.
 *   The easiest way to discover all available parameters is to visit the API Explorer on your CiviCRM site.
 *   The API Explorer is listed in the CiviCRM menu under Support -> Developer.
 *
 * @param string|int|array $index Controls the Result array format.
 *   By default the api Result contains a non-associative array of data. Passing an $index tells the api to
 *   automatically reformat the array, depending on the variable type passed:
 *   - **Integer:** return a single result array;
 *     e.g. `$index = 0` will return the first result, 1 will return the second, and -1 will return the last.
 *   - **String:** index the results by a field value;
 *     e.g. `$index = "name"` will return an associative array with the field 'name' as keys.
 *   - **Non-associative array:** return a single value from each result;
 *     e.g. `$index = ['title']` will return a non-associative array of strings - the 'title' field from each result.
 *   - **Associative array:** a combination of the previous two modes;
 *     e.g. `$index = ['name' => 'title']` will return an array of strings - the 'title' field keyed by the 'name' field.
 *
 * @return \Civi\Api4\Generic\Result
 * @throws \CRM_Core_Exception
 * @throws \Civi\API\Exception\NotImplementedException
 */
function civicrm_api4(string $entity, string $action, array $params = [], $index = NULL) {
  $indexField = $index && is_string($index) && !CRM_Utils_Rule::integer($index) ? $index : NULL;
  $removeIndexField = FALSE;

  // If index field is not part of the select query, we add it here and remove it below (except for oddball "Setting" api)
  if ($indexField && !empty($params['select']) && is_array($params['select']) && !($entity === 'Setting' && $action === 'get') && !\Civi\Api4\Utils\SelectUtil::isFieldSelected($indexField, $params['select'])) {
    $params['select'][] = $indexField;
    $removeIndexField = TRUE;
  }
  $apiCall = \Civi\API\Request::create($entity, $action, ['version' => 4] + $params);

  if ($index && is_array($index)) {
    $indexCol = reset($index);
    $indexField = key($index);
    // Automatically add index fields(s) to the SELECT clause
    if ($entity !== 'Setting' && method_exists($apiCall, 'addSelect')) {
      $apiCall->addSelect($indexCol);
      if ($indexField && $indexField != $indexCol) {
        $apiCall->addSelect($indexField);
      }
    }
  }

  $result = $apiCall->execute();

  // Index results by key
  if ($indexField) {
    $result->indexBy($indexField);
    if ($removeIndexField) {
      foreach ($result as $key => $value) {
        unset($result[$key][$indexField]);
      }
    }
  }
  // Return result at index
  elseif (CRM_Utils_Rule::integer($index)) {
    $item = $result->itemAt($index);
    if (is_null($item)) {
      throw new \CRM_Core_Exception("Index $index not found in api results");
    }
    // Attempt to return a Result object if item is array, otherwise just return the item
    if (!is_array($item)) {
      return $item;
    }
    $result->exchangeArray($item);
  }
  if (!empty($indexCol)) {
    $result->exchangeArray($result->column($indexCol));
  }
  return $result;
}

/**
 * Version 3 wrapper for civicrm_api.
 *
 * Throws exception.
 *
 * @param string $entity
 * @param string $action
 * @param array $params
 *
 * @throws CRM_Core_Exception
 *
 * @return array|int
 *   Dependent on the $action
 */
function civicrm_api3(string $entity, string $action, array $params = []) {
  $params['version'] = 3;
  $result = \Civi::service('civi_api_kernel')->runSafe($entity, $action, $params);
  if (is_array($result) && !empty($result['is_error'])) {
    throw new CRM_Core_Exception($result['error_message'], $result['error_code'] ?? 'undefined', $result);
  }
  return $result;
}

/**
 * Call getfields from api wrapper.
 *
 * This function ensures that settings that
 * could alter getfields output (e.g. action for all api & profile_id for
 * profile api ) are consistently passed in.
 *
 * We check whether the api call is 'getfields' because if getfields is
 * being called we return an empty array as no alias swapping, validation or
 * default filling is done on getfields & we want to avoid a loop
 *
 * @todo other output modifiers include contact_type
 *
 * @param array $apiRequest
 *
 * @return array
 *   getfields output
 */
function _civicrm_api3_api_getfields(&$apiRequest) {
  if (strtolower($apiRequest['action'] == 'getfields')) {
    // the main param getfields takes is 'action' - however this param is not compatible with REST
    // so we accept 'api_action' as an alias of action on getfields
    return ['action' => ['api.aliases' => ['api_action']]];
  }
  $getFieldsParams = ['action' => $apiRequest['action']];
  $entity = $apiRequest['entity'];
  if ($entity == 'Profile' && array_key_exists('profile_id', $apiRequest['params'])) {
    $getFieldsParams['profile_id'] = $apiRequest['params']['profile_id'];
  }
  $fields = civicrm_api3($entity, 'getfields', $getFieldsParams);
  return $fields['values'];
}

/**
 * Check if the result is an error. Note that this function has been retained from
 * api v2 for convenience but the result is more standardised in v3 and param
 * 'format.is_success' => 1
 * will result in a boolean success /fail being returned if that is what you need.
 *
 * @param mixed $result
 *
 * @return bool
 *   true if error, false otherwise
 */
function civicrm_error($result) {
  return is_array($result) && !empty($result['is_error']);
}

/**
 * Get camel case version of entity name.
 *
 * @param string|null $entity
 *
 * @return string|null
 */
function _civicrm_api_get_camel_name($entity) {
  return is_string($entity) ? \Civi\API\Request::normalizeEntityName($entity) : NULL;
}

/**
 * Swap out any $values vars.
 *
 * Ie. the value after $value is swapped for the parent $result
 * 'activity_type_id' => '$value.testfield',
 * 'tag_id'  => '$value.api.tag.create.id',
 * 'tag1_id' => '$value.api.entity.create.0.id'
 *
 * @param array $params
 * @param array $parentResult
 * @param string $separator
 */
function _civicrm_api_replace_variables(&$params, &$parentResult, $separator = '.') {
  foreach ($params as $field => &$value) {
    if (substr($field, 0, 4) == 'api.') {
      // CRM-21246 - Leave nested calls alone.
      continue;
    }
    if (is_string($value) && substr($value, 0, 6) == '$value') {
      $value = _civicrm_api_replace_variable($value, $parentResult, $separator);
    }
    // Handle the operator syntax: array('OP' => $val)
    elseif (is_array($value) && is_string(reset($value)) && substr(reset($value), 0, 6) == '$value') {
      $key = key($value);
      $value[$key] = _civicrm_api_replace_variable($value[$key], $parentResult, $separator);
      // A null value with an operator will cause an error, so remove it.
      if ($value[$key] === NULL) {
        $value = '';
      }
    }
  }
}

/**
 * Swap out a $value.foo variable with the value from parent api results.
 *
 * Called by _civicrm_api_replace_variables to do the substitution.
 *
 * @param string $value
 * @param array $parentResult
 * @param string $separator
 * @return mixed|null
 */
function _civicrm_api_replace_variable($value, $parentResult, $separator) {
  $valueSubstitute = substr($value, 7);

  if (!empty($parentResult[$valueSubstitute])) {
    return $parentResult[$valueSubstitute];
  }
  else {
    $stringParts = explode($separator, $value);
    unset($stringParts[0]);
    // CRM-16168 If we have failed to swap it out we should unset it rather than leave the placeholder.
    $value = NULL;

    $fieldname = array_shift($stringParts);

    //when our string is an array we will treat it as an array from that . onwards
    $count = count($stringParts);
    while ($count > 0) {
      $fieldname .= "." . array_shift($stringParts);
      if (array_key_exists($fieldname, $parentResult) && is_array($parentResult[$fieldname])) {
        $arrayLocation = $parentResult[$fieldname];
        foreach ($stringParts as $key => $innerValue) {
          $arrayLocation = $arrayLocation[$innerValue] ?? NULL;
        }
        $value = $arrayLocation;
      }
      $count = count($stringParts);
    }
  }
  return $value;
}

/**
 * Convert possibly camel name to underscore separated entity name.
 *
 * @param string $entity
 *   Entity name in various formats e.g. Contribution, contribution,
 *   OptionValue, option_value, UFJoin, uf_join.
 *
 * @return string
 *   Entity name in underscore separated format.
 *
 * @deprecated
 */
function _civicrm_api_get_entity_name_from_camel($entity) {
  if (!$entity) {
    // @todo - this should not be called when empty.
    return '';
  }
  return CRM_Core_DAO_AllCoreTables::convertEntityNameToLower($entity);
}

/**
 * Having a DAO object find the entity name.
 *
 * @param CRM_Core_DAO $bao
 *   DAO being passed in.
 *
 * @return string
 */
function _civicrm_api_get_entity_name_from_dao($bao) {
  return CRM_Core_DAO_AllCoreTables::getBriefName(get_class($bao));
}<?php

/**
 *
 * This class allows to consume the API, either from within a module that knows civicrm already:
 *
 * ```
 *   require_once('api/class.api.php');
 *   $api = new civicrm_api3();
 * ```
 *
 * or from any code on the same server as civicrm
 *
 * ```
 *   require_once('/your/civi/folder/api/class.api.php');
 *   // the path to civicrm.settings.php
 *   $api = new civicrm_api3 (['conf_path'=> '/your/path/to/your/civicrm/or/joomla/site']);
 * ```
 *
 * or to query a remote server via the rest api
 *
 * ```
 *   $api = new civicrm_api3 (['server' => 'http://example.org',
 *                             'api_key'=>'theusersecretkey',
 *                             'key'=>'thesitesecretkey']);
 * ```
 *
 * No matter how initialised and if civicrm is local or remote, you use the class the same way.
 *
 * ```
 *   $api->{entity}->{action}($params);
 * ```
 *
 * So, to get the individual contacts:
 *
 * ```
 *   if ($api->Contact->Get(['contact_type'=>'Individual','return'=>'sort_name,current_employer']) {
 *     // each key of the result array is an attribute of the api
 *     echo "\n contacts found " . $api->count;
 *     foreach ($api->values as $c) {
 *       echo "\n".$c->sort_name. " working for ". $c->current_employer;
 *     }
 *     // in theory, doesn't append
 *   } else {
 *     echo $api->errorMsg();
 *   }
 * ```
 *
 * Or, to create an event:
 *
 * ```
 *   if ($api->Event->Create(['title'=>'Test','event_type_id' => 1,'is_public' => 1,'start_date' => 19430429])) {
 *     echo "created event id:". $api->id;
 *   } else {
 *     echo $api->errorMsg();
 *   }
 * ```
 *
 * To make it easier, the Actions can either take for input an
 * associative array $params, or simply an id. The following two lines
 * are equivalent.
 *
 * ```
 *   $api->Activity->Get (42);
 *   $api->Activity->Get (['id'=>42]);
 * ```
 *
 *
 * You can also get the result like civicrm_api does, but as an object
 * instead of an array (eg $entity->attribute instead of
 * $entity['attribute']).
 *
 * ```
 *   $result = $api->result;
 *   // is the json encoded result
 *   echo $api;
 * ```
 *
 * For remote calls, you may need to set the UserAgent and Referer strings for some environments (eg WordFence)
 * Add 'referer' and 'useragent' to the initialisation config:
 *
 * ```
 *   $api = new civicrm_api3 (['server' => 'http://example.org',
 *                             'api_key'=>'theusersecretkey',
 *                             'key'=>'thesitesecretkey',
 *                             'referer'=>'https://my_site',
 *                             'useragent'=>'curl']);
 * ```
 */
class civicrm_api3 {

  /**
   * Are we performing a local or remote API call?
   *
   * @var bool
   */
  public $local = TRUE;

  /**
   * Array of inputs to pass to `call`, if param not passed directly
   *
   * @var array
   * @internal
   */
  public $input = [];

  /**
   * Holds the result of the last API request.
   * If the request has not yet run, lastResult will be empty.
   *
   * @var \stdClass
   * @internal
   */
  public $lastResult;

  /**
   * When making a remote API request,
   * $uri will be the path to the remote server's API endpoint
   *
   * @var string|null
   * @internal
   */
  public $uri = NULL;

  /**
   * When making a remote API request,
   * $key will be sent as part of the request
   *
   * @var string|null
   * @internal
   */
  public $key = NULL;

  /**
   * When making a remote API request,
   * $api_key will be sent as part of the request
   *
   * @var string|null
   * @internal
   */
  public $api_key = NULL;

  /**
   * When making a remote API request,
   * $referer holds the Referer header value to be sent as part of the request
   *
   * @var string|null
   * @internal
   */
  public $referer = NULL;

  /**
   * When making a remote API request,
   * $useragent holds the User-Agent header value to be sent as part of the request
   *
   * @var string|null
   * @internal
   */
  public $useragent = NULL;

  /**
   * Reference to the CRM_Core_Config singleton
   *
   * @var CRM_Core_Config
   */
  protected $cfg;

  /**
   * The current entity, which actions should be performed against
   *
   * @var string|null
   */
  protected $currentEntity = NULL;

  /**
   * Class constructor.
   *
   * @param array $config API configuration.
   */
  public function __construct($config = NULL) {
    $this->local      = TRUE;
    $this->input      = [];
    $this->lastResult = new stdClass();
    if (!empty($config) && !empty($config['server'])) {
      // we are calling a remote server via REST
      $this->local = FALSE;
      $this->uri = $config['server'];
      if (!empty($config['path'])) {
        $this->uri .= "/" . $config['path'];
      }
      else {
        $this->uri .= '/sites/all/modules/civicrm/extern/rest.php';
      }
      if (!empty($config['key'])) {
        $this->key = $config['key'];
      }
      else {
        die("\nFATAL:param['key] missing\n");
      }
      if (!empty($config['api_key'])) {
        $this->api_key = $config['api_key'];
      }
      else {
        die("\nFATAL:param['api_key] missing\n");
      }
      $this->referer = !empty($config['referer']) ? $config['referer'] : '';
      $this->useragent = !empty($config['useragent']) ? $config['useragent'] : 'curl';
      return;
    }
    if (!empty($config) && !empty($config['conf_path'])) {
      if (!defined('CIVICRM_SETTINGS_PATH')) {
        define('CIVICRM_SETTINGS_PATH', $config['conf_path'] . '/civicrm.settings.php');
      }
      require_once CIVICRM_SETTINGS_PATH;
      require_once 'CRM/Core/ClassLoader.php';
      require_once 'api/api.php';
      require_once "api/v3/utils.php";
      CRM_Core_ClassLoader::singleton()->register();
      $this->cfg = CRM_Core_Config::singleton();
      $this->init();
    }
    else {
      $this->cfg = CRM_Core_Config::singleton();
    }
  }

  /**
   * Convert to string.
   *
   * @return string
   */
  public function __toString() {
    return json_encode($this->lastResult);
  }

  /**
   * Perform action.
   *
   * @param string $action
   * @param array $params
   *
   * @return bool
   */
  public function __call($action, $params) {
    // @TODO Check if it's a valid action.
    if (isset($params[0])) {
      return $this->call($this->currentEntity, $action, $params[0]);
    }
    else {
      return $this->call($this->currentEntity, $action, $this->input);
    }
  }

  /**
   * Call via rest.
   *
   * @param string $entity
   * @param string $action
   * @param array $params
   *
   * @return \stdClass
   */
  private function remoteCall($entity, $action, $params = []) {
    $query = $this->uri . "?entity=$entity&action=$action";
    $fields = http_build_query([
      'key' => $this->key,
      'api_key' => $this->api_key,
      'json' => json_encode($params),
    ]);

    if (function_exists('curl_init')) {
      // To facilitate debugging without leaking info, entity & action
      // are GET, other data is POST.
      $ch = curl_init();
      curl_setopt($ch, CURLOPT_URL, $query);
      curl_setopt($ch, CURLOPT_POST, TRUE);
      curl_setopt($ch, CURLOPT_POSTFIELDS, $fields);
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
      curl_setopt($ch, CURLOPT_USERAGENT, $this->useragent);
      if ($this->referer) {
        curl_setopt($ch, CURLOPT_REFERER, $this->referer);
      }
      $result = curl_exec($ch);
      // CiviCRM expects to get back a CiviCRM error object.
      if (curl_errno($ch)) {
        $res = new stdClass();
        $res->is_error = 1;
        $res->error_message = curl_error($ch);
        $res->level = "cURL";
        $res->error = ['cURL error' => curl_error($ch)];
        return $res;
      }
      curl_close($ch);
    }
    else {
      // Should be discouraged, because the API credentials and data
      // are submitted as GET data, increasing chance of exposure..
      $result = file_get_contents($query . '&' . $fields);
    }
    if (!$res = json_decode($result)) {
      $res = new stdClass();
      $res->is_error = 1;
      $res->error_message = 'Unable to parse returned JSON';
      $res->level = 'json_decode';
      $res->error = ['Unable to parse returned JSON' => $result];
      $res->row_result = $result;
    }
    return $res;
  }

  /**
   * Call api function.
   *
   * @param string $entity
   * @param string $action
   * @param array $params
   *
   * @return bool
   */
  private function call($entity, $action = 'Get', $params = []) {
    if (is_int($params)) {
      $params = ['id' => $params];
    }
    elseif (is_string($params)) {
      $params = json_decode($params);
    }

    if (!isset($params['version'])) {
      $params['version'] = 3;
    }
    if (!isset($params['sequential'])) {
      $params['sequential'] = 1;
    }

    if (!$this->local) {
      $this->lastResult = $this->remoteCall($entity, $action, $params);
    }
    else {
      // Converts a multi-dimentional array into an object.
      $this->lastResult = json_decode(json_encode(civicrm_api($entity, $action, $params)));
    }
    // Reset the input to be ready for a new call.
    $this->input = [];
    if (property_exists($this->lastResult, 'is_error')) {
      return !$this->lastResult->is_error;
    }
    // getsingle doesn't have is_error.
    return TRUE;
  }

  /**
   * Helper method for long running programs (eg bots).
   */
  public function ping() {
    global $_DB_DATAOBJECT;
    foreach ($_DB_DATAOBJECT['CONNECTIONS'] as & $c) {
      if (!$c->connection->ping()) {
        $c->connect($this->cfg->dsn);
        if (!$c->connection->ping()) {
          die("we couldn't connect");
        }
      }
    }
  }

  /**
   * Return the last error message.
   * @return string
   */
  public function errorMsg() {
    return $this->lastResult->error_message;
  }

  /**
   * Initialize.
   */
  public function init() {
    CRM_Core_DAO::init($this->cfg->dsn);
  }

  /**
   * Get attribute.
   *
   * @param string $name
   * @param mixed $value
   *
   * @return $this
   */
  public function attr($name, $value = NULL) {
    if ($value === NULL) {
      if (property_exists($this->lastResult, $name)) {
        return $this->lastResult->$name;
      }
    }
    else {
      $this->input[$name] = $value;
    }
    return $this;
  }

  /**
   * Is this an error.
   *
   * @return bool
   */
  public function is_error() {
    return (property_exists($this->lastResult, 'is_error') && $this->lastResult->is_error);
  }

  /**
   * Check if var is set.
   *
   * @param string $name
   *
   * @return bool
   */
  public function is_set($name) {
    return (isset($this->lastResult->$name));
  }

  /**
   * Get object.
   *
   * @param string $name
   *
   * @return $this
   */
  public function __get($name) {
    // @TODO Test if valid entity.
    if (strtolower($name) !== $name) {
      // Cheap and dumb test to differentiate call to
      // $api->Entity->Action & value retrieval.
      $this->currentEntity = $name;
      return $this;
    }
    if ($name === 'result') {
      return $this->lastResult;
    }
    if ($name === 'values') {
      return $this->lastResult->values;
    }
    if (property_exists($this->lastResult, $name)) {
      return $this->lastResult->$name;
    }
    $this->currentEntity = $name;
    return $this;
  }

  /**
   * Or use $api->value.
   * @return array
   */
  public function values() {
    if (is_array($this->lastResult)) {
      return $this->lastResult['values'];
    }
    else {
      return $this->lastResult->values;
    }
  }

  /**
   * Or use $api->result.
   * @return array
   */
  public function result() {
    return $this->lastResult;
  }

}<?php
/*
 +--------------------------------------------------------------------+
 | Copyright CiviCRM LLC. All rights reserved.                        |
 |                                                                    |
 | This work is published under the GNU AGPLv3 license with some      |
 | permitted exceptions and without any warranty. For full license    |
 | and copyright information, see https://civicrm.org/licensing       |
 +--------------------------------------------------------------------+
 */

/**
 * @package CiviCRM_APIv3
 */

/**
 * Adjust Metadata for Transact action.
 *
 * The metadata is used for setting defaults, documentation & validation.
 *
 * @param array $params
 *   Array of parameters determined by getfields.
 */
function _civicrm_api3_contribution_transact_spec(&$params) {
  $fields = civicrm_api3('Contribution', 'getfields', ['action' => 'create']);
  $params = array_merge($params, $fields['values']);
  $params['receive_date']['api.default'] = 'now';
}

/**
 * Process a transaction and record it against the contact.
 *
 * @deprecated
 *
 * @param array $params
 *   Input parameters.
 *
 * @return array
 *   contribution of created or updated record (or a civicrm error)
 */
function civicrm_api3_contribution_transact($params) {
  CRM_Core_Error::deprecatedFunctionWarning('The contibution.transact api is unsupported & known to have issues. Please see the section at the bottom of https://docs.civicrm.org/dev/en/latest/financial/orderAPI/ for getting off it');
  // Set some params specific to payment processing
  // @todo - fix this function - none of the results checked by civicrm_error would ever be an array with
  // 'is_error' set
  // also trxn_id is not saved.
  // but since there is no test it's not desirable to jump in & make the obvious changes.
  $params['payment_processor_mode'] = empty($params['is_test']) ? 'live' : 'test';
  $params['amount'] = $params['total_amount'];
  if (!isset($params['net_amount'])) {
    $params['net_amount'] = $params['amount'];
  }
  if (!isset($params['invoiceID']) && isset($params['invoice_id'])) {
    $params['invoiceID'] = $params['invoice_id'];
  }

  // Some payment processors expect a unique invoice_id - generate one if not supplied
  $params['invoice_id'] = CRM_Utils_Array::value('invoice_id', $params, md5(uniqid(rand(), TRUE)));

  $paymentProcessor = CRM_Financial_BAO_PaymentProcessor::getPayment($params['payment_processor'], $params['payment_processor_mode']);
  $params = $paymentProcessor['object']->doPayment($params);

  $params['payment_instrument_id'] = $paymentProcessor['object']->getPaymentInstrumentID();

  return civicrm_api('Contribution', 'create', $params);
}## This file contains a list of INI fields that may
## be returned by the System.get API.
# Omit: SMTP
allow_call_time_pass_reference
allow_url_fopen
allow_url_include
always_populate_raw_post_data
apc.cache_by_default
apc.canonicalize
apc.coredump_unmap
apc.enable_cli
apc.enabled
apc.file_md5
apc.file_update_protection
# Omit: apc.filters
apc.gc_ttl
apc.include_once_override
apc.lazy_classes
apc.lazy_functions
apc.max_file_size
# Omit: apc.mmap_file_mask
apc.num_files_hint
# Omit: apc.preload_path
apc.report_autofilter
apc.rfc1867
apc.rfc1867_freq
# Omit: apc.rfc1867_name
# Omit: apc.rfc1867_prefix
apc.rfc1867_ttl
apc.serializer
apc.shm_segments
apc.shm_size
apc.slam_defense
apc.stat
apc.stat_ctime
apc.ttl
apc.use_request_time
apc.user_entries_hint
apc.user_ttl
apc.write_lock
arg_separator.input
arg_separator.output
asp_tags
assert.active
assert.bail
# Omit: assert.callback
assert.quiet_eval
assert.warning
# Omit: auto_append_file
auto_detect_line_endings
auto_globals_jit
# Omit: auto_prepend_file
bcmath.scale
# Omit: browscap
# Omit: curl.cainfo
date.default_latitude
date.default_longitude
date.sunrise_zenith
date.sunset_zenith
date.timezone
# Omit: dba.default_handler
default_charset
default_mimetype
default_socket_timeout
define_syslog_variables
disable_classes
disable_functions
display_errors
display_startup_errors
# Omit: doc_root
# Omit: docref_ext
# Omit: docref_root
enable_dl
enable_post_data_reading
# Omit: error_append_string
# Omit: error_log
# Omit: error_prepend_string
error_reporting
exif.decode_jis_intel
exif.decode_jis_motorola
exif.decode_unicode_intel
exif.decode_unicode_motorola
exif.encode_jis
exif.encode_unicode
exit_on_timeout
expose_php
# Omit: extension_dir
file_uploads
filter.default
filter.default_flags
# Omit: from
gd.jpeg_ignore_warning
highlight.bg
highlight.comment
highlight.default
highlight.html
highlight.keyword
highlight.string
html_errors
iconv.input_encoding
iconv.internal_encoding
iconv.output_encoding
ignore_repeated_errors
ignore_repeated_source
ignore_user_abort
implicit_flush
# Omit: include_path
intl.default_locale
intl.error_level
ldap.max_links
log_errors
log_errors_max_len
magic_quotes_gpc
magic_quotes_runtime
magic_quotes_sybase
mail.add_x_header
# Omit: mail.force_extra_parameters
# Omit: mail.log
max_execution_time
max_file_uploads
max_input_nesting_level
max_input_time
max_input_vars
mbstring.detect_order
mbstring.encoding_translation
mbstring.func_overload
mbstring.http_input
mbstring.http_output
mbstring.http_output_conv_mimetypes
mbstring.internal_encoding
mbstring.language
mbstring.strict_detection
mbstring.substitute_character
# Omit: mcrypt.algorithms_dir
# Omit: mcrypt.modes_dir
memory_limit
mysql.allow_local_infile
mysql.allow_persistent
mysql.connect_timeout
# Omit: mysql.default_host
# Omit: mysql.default_password
# Omit: mysql.default_port
# Omit: mysql.default_socket
# Omit: mysql.default_user
mysql.max_links
mysql.max_persistent
mysql.trace_mode
mysqli.allow_local_infile
mysqli.allow_persistent
# Omit: mysqli.default_host
# Omit: mysqli.default_port
# Omit: mysqli.default_pw
# Omit: mysqli.default_socket
# Omit: mysqli.default_user
mysqli.max_links
mysqli.max_persistent
mysqli.reconnect
# Omit: open_basedir
output_buffering
output_handler
pcre.backtrack_limit
pcre.recursion_limit
# Omit: pdo_mysql.default_socket
pgsql.allow_persistent
pgsql.auto_reset_persistent
pgsql.ignore_notice
pgsql.log_notice
pgsql.max_links
pgsql.max_persistent
# Omit: phar.cache_list
phar.readonly
phar.require_hash
post_max_size
precision
realpath_cache_size
realpath_cache_ttl
register_argc_argv
register_globals
register_long_arrays
report_memleaks
report_zend_debug
request_order
# Omit: safe_mode_allowed_env_vars
# Omit: safe_mode_exec_dir
safe_mode_gid
# Omit: safe_mode_include_dir
# Omit: safe_mode_protected_env_vars
# Omit: sendmail_from
# Omit: sendmail_path
serialize_precision
session.auto_start
session.bug_compat_42
session.bug_compat_warn
session.cache_expire
# Omit: session.cache_limiter
# Omit: session.cookie_domain
session.cookie_httponly
session.cookie_lifetime
# Omit: session.cookie_path
session.cookie_secure
# Omit: session.entropy_file
# Omit: session.entropy_length
session.gc_divisor
session.gc_maxlifetime
session.gc_probability
# Omit: session.hash_bits_per_character
session.hash_function
# Omit: session.name
session.referer_check
# Omit: session.save_handler
# Omit: session.save_path
session.serialize_handler
session.upload_progress.cleanup
session.upload_progress.enabled
session.upload_progress.freq
session.upload_progress.min_freq
# Omit: session.upload_progress.name
# Omit: session.upload_progress.prefix
session.use_cookies
session.use_only_cookies
session.use_trans_sid
short_open_tag
# Omit: smtp_port
soap.wsdl_cache
# Omit: soap.wsdl_cache_dir
soap.wsdl_cache_enabled
soap.wsdl_cache_limit
soap.wsdl_cache_ttl
sql.safe_mode
# Omit: sqlite3.extension_dir
track_errors
# Omit: unserialize_callback_func
upload_max_filesize
# Omit: upload_tmp_dir
url_rewriter.tags
user_agent
# Omit: user_dir
user_ini.cache_ttl
# Omit: user_ini.filename
variables_order
xmlrpc_error_number
xmlrpc_errors
# Omit:'xsl.security_prefs
y2k_compliance
yaz.keepalive
# Omit: yaz.log_file
yaz.log_mask
yaz.max_links
zend.detect_unicode
zend.enable_gc
zend.multibyte
zend.script_encoding
zlib.output_compression
zlib.output_compression_level
# Omit: zlib.output_handler
auto_increment_increment
auto_increment_offset
autocommit
automatic_sp_privileges
back_log
#|| basedir                                           | /Applications/MAMP/Library/                                                                                            |
big_tables
binlog_cache_size
binlog_direct_non_transactional_updates
binlog_format
binlog_stmt_cache_size
bulk_insert_buffer_size
character_set_client
character_set_connection
character_set_database
character_set_filesystem
character_set_results
character_set_server
character_set_system
#|| character_sets_dir                                | /Applications/MAMP/Library/share/charsets/                                                                             |
collation_connection
collation_database
collation_server
#|| completion_type                                   | NO_CHAIN                                                                                                               |
concurrent_insert
connect_timeout
#|| datadir                                           | /Users/foobar/.amp/ram_disk/mysql/                                                                                     |
date_format
datetime_format
default_storage_engine
default_week_format
delay_key_write
delayed_insert_limit
delayed_insert_timeout
delayed_queue_size
#|| div_precision_increment                           | 4                                                                                                                      |
#|| engine_condition_pushdown                         | ON                                                                                                                     |
error_count
#|| event_scheduler                                   | OFF                                                                                                                    |
#|| expire_logs_days                                  | 0                                                                                                                      |
#|| external_user                                     |                                                                                                                        |
flush
flush_time
foreign_key_checks
ft_boolean_syntax
ft_max_word_len
ft_min_word_len
ft_query_expansion_limit
#|| ft_stopword_file                                  | (built-in)                                                                                                             |
#|| general_log                                       | OFF                                                                                                                    |
#|| general_log_file                                  | /Users/foobar/.amp/ram_disk/mysql/whizbangz.log                                                                        |
group_concat_max_len
have_compress
have_crypt
have_csv
have_dynamic_loading
have_geometry
have_innodb
have_ndbcluster
have_openssl
have_partitioning
have_profiling
have_query_cache
have_rtree_keys
have_ssl
have_symlink
#|| hostname                                          | whizbangz.local                                                                                                        |
#|| identity                                          | 0                                                                                                                      |
ignore_builtin_innodb
#|| init_connect                                      |                                                                                                                        |
#|| init_file                                         |                                                                                                                        |
#|| init_slave                                        |                                                                                                                        |
innodb_adaptive_flushing
innodb_adaptive_hash_index
innodb_additional_mem_pool_size
innodb_autoextend_increment
innodb_autoinc_lock_mode
innodb_buffer_pool_instances
innodb_buffer_pool_size
#|| innodb_change_buffering                           | all                                                                                                                    |
#|| innodb_checksums                                  | ON                                                                                                                     |
innodb_commit_concurrency
innodb_concurrency_tickets
#|| innodb_data_file_path                             | ibdata1:10M:autoextend                                                                                                 |
#|| innodb_data_home_dir                              |                                                                                                                        |
innodb_doublewrite
innodb_fast_shutdown
innodb_file_format
innodb_file_format_check
innodb_file_format_max
innodb_file_per_table
innodb_flush_log_at_trx_commit
#|| innodb_flush_method                               |                                                                                                                        |
#|| innodb_force_load_corrupted                       | OFF                                                                                                                    |
#|| innodb_force_recovery                             | 0                                                                                                                      |
innodb_io_capacity
#|| innodb_large_prefix                               | OFF                                                                                                                    |
innodb_lock_wait_timeout
#|| innodb_locks_unsafe_for_binlog                    | OFF                                                                                                                    |
innodb_log_buffer_size
innodb_log_file_size
innodb_log_files_in_group
#|| innodb_log_group_home_dir                         | ./                                                                                                                     |
#|| innodb_max_dirty_pages_pct                        | 75                                                                                                                     |
#|| innodb_max_purge_lag                              | 0                                                                                                                      |
#|| innodb_mirrored_log_groups                        | 1                                                                                                                      |
#|| innodb_old_blocks_pct                             | 37                                                                                                                     |
#|| innodb_old_blocks_time                            | 0                                                                                                                      |
innodb_open_files
innodb_print_all_deadlocks
#|| innodb_purge_batch_size                           | 20                                                                                                                     |
#|| innodb_purge_threads                              | 0                                                                                                                      |
#|| innodb_random_read_ahead                          | OFF                                                                                                                    |
#|| innodb_read_ahead_threshold                       | 56                                                                                                                     |
#|| innodb_read_io_threads                            | 4                                                                                                                      |
innodb_replication_delay
innodb_rollback_on_timeout
innodb_rollback_segments
innodb_spin_wait_delay
innodb_stats_method
#|| innodb_stats_on_metadata                          | ON                                                                                                                     |
#|| innodb_stats_sample_pages                         | 8                                                                                                                      |
innodb_strict_mode
innodb_support_xa
innodb_sync_spin_loops
innodb_table_locks
innodb_thread_concurrency
#|| innodb_thread_sleep_delay                         | 10000                                                                                                                  |
#|| innodb_use_native_aio                             | OFF                                                                                                                    |
#|| innodb_use_sys_malloc                             | ON                                                                                                                     |
innodb_version
innodb_write_io_threads
#|| insert_id                                         | 0                                                                                                                      |
#|| interactive_timeout                               | 28800                                                                                                                  |
join_buffer_size
#|| keep_files_on_create                              | OFF                                                                                                                    |
key_buffer_size
key_cache_age_threshold
key_cache_block_size
key_cache_division_limit
large_files_support
large_page_size
large_pages
#|| last_insert_id                                    | 0                                                                                                                      |
lc_messages
#|| lc_messages_dir                                   | /Applications/MAMP/Library/share/                                                                                      |
lc_time_names
#|| license                                           | GPL                                                                                                                    |
#|| local_infile                                      | ON                                                                                                                     |
lock_wait_timeout
#|| locked_in_memory                                  | OFF                                                                                                                    |
#|| log                                               | OFF                                                                                                                    |
#|| log_bin                                           | OFF                                                                                                                    |
#|| log_bin_trust_function_creators                   | OFF                                                                                                                    |
#|| log_error                                         |                                                                                                                        |
#|| log_output                                        | FILE                                                                                                                   |
#|| log_queries_not_using_indexes                     | OFF                                                                                                                    |
#|| log_slave_updates                                 | OFF                                                                                                                    |
#|| log_slow_queries                                  | OFF                                                                                                                    |
#|| log_warnings                                      | 1                                                                                                                      |
long_query_time
#|| low_priority_updates                              | OFF                                                                                                                    |
lower_case_file_system
lower_case_table_names
max_allowed_packet
max_binlog_cache_size
max_binlog_size
max_binlog_stmt_cache_size
max_connect_errors
max_connections
max_delayed_threads
max_error_count
max_heap_table_size
max_insert_delayed_threads
max_join_size
max_length_for_sort_data
max_long_data_size
max_prepared_stmt_count
max_relay_log_size
max_seeks_for_key
max_sort_length
max_sp_recursion_depth
max_tmp_tables
max_user_connections
max_write_lock_count
metadata_locks_cache_size
#|| min_examined_row_limit                            | 0                                                                                                                      |
#|| multi_range_count                                 | 256                                                                                                                    |
#|| myisam_data_pointer_size                          | 6                                                                                                                      |
#|| myisam_max_sort_file_size                         | 9223372036853727232                                                                                                    |
#|| myisam_mmap_size                                  | 18446744073709551615                                                                                                   |
#|| myisam_recover_options                            | OFF                                                                                                                    |
#|| myisam_repair_threads                             | 1                                                                                                                      |
#|| myisam_sort_buffer_size                           | 8388608                                                                                                                |
#|| myisam_stats_method                               | nulls_unequal                                                                                                          |
#|| myisam_use_mmap                                   | OFF                                                                                                                    |
net_buffer_length
net_read_timeout
net_retry_count
net_write_timeout
#|| new                                               | OFF                                                                                                                    |
#|| old                                               | OFF                                                                                                                    |
#|| old_alter_table                                   | OFF                                                                                                                    |
#|| old_passwords                                     | OFF                                                                                                                    |
#|| open_files_limit                                  | 961                                                                                                                    |
optimizer_prune_level
optimizer_search_depth
#|| optimizer_switch                                  | index_merge=on,index_merge_union=on,index_merge_sort_union=on,index_merge_intersection=on,engine_condition_pushdown=on |
#|| performance_schema                                | OFF                                                                                                                    |
#|| performance_schema_events_waits_history_long_size | 10000                                                                                                                  |
#|| performance_schema_events_waits_history_size      | 10                                                                                                                     |
#|| performance_schema_max_cond_classes               | 80                                                                                                                     |
#|| performance_schema_max_cond_instances             | 1000                                                                                                                   |
#|| performance_schema_max_file_classes               | 50                                                                                                                     |
#|| performance_schema_max_file_handles               | 32768                                                                                                                  |
#|| performance_schema_max_file_instances             | 10000                                                                                                                  |
#|| performance_schema_max_mutex_classes              | 200                                                                                                                    |
#|| performance_schema_max_mutex_instances            | 1000000                                                                                                                |
#|| performance_schema_max_rwlock_classes             | 30                                                                                                                     |
#|| performance_schema_max_rwlock_instances           | 1000000                                                                                                                |
#|| performance_schema_max_table_handles              | 100000                                                                                                                 |
#|| performance_schema_max_table_instances            | 50000                                                                                                                  |
#|| performance_schema_max_thread_classes             | 50                                                                                                                     |
#|| performance_schema_max_thread_instances           | 1000                                                                                                                   |
#|| pid_file                                          | /Users/foobar/.amp/ram_disk/tmp/mysqld.pid                                                                             |
#|| plugin_dir                                        | /Applications/MAMP/Library/lib/plugin/                                                                                 |
#|| port                                              | 3307                                                                                                                   |
#|| preload_buffer_size                               | 32768                                                                                                                  |
profiling
profiling_history_size
protocol_version
#|| proxy_user                                        |                                                                                                                        |
#|| pseudo_slave_mode                                 | OFF                                                                                                                    |
#|| pseudo_thread_id                                  | 834                                                                                                                    |
query_alloc_block_size
query_cache_limit
query_cache_min_res_unit
query_cache_size
query_cache_type
query_cache_wlock_invalidate
query_prealloc_size
#|| rand_seed1                                        | 0                                                                                                                      |
#|| rand_seed2                                        | 0                                                                                                                      |
#|| range_alloc_block_size                            | 4096                                                                                                                   |
read_buffer_size
read_only
read_rnd_buffer_size
#|| relay_log                                         |                                                                                                                        |
#|| relay_log_index                                   |                                                                                                                        |
#|| relay_log_info_file                               | relay-log.info                                                                                                         |
#|| relay_log_purge                                   | ON                                                                                                                     |
#|| relay_log_recovery                                | OFF                                                                                                                    |
#|| relay_log_space_limit                             | 0                                                                                                                      |
#|| report_host                                       |                                                                                                                        |
#|| report_password                                   |                                                                                                                        |
#|| report_port                                       | 3307                                                                                                                   |
#|| report_user                                       |                                                                                                                        |
#|| rpl_recovery_rank                                 | 0                                                                                                                      |
#|| secure_auth                                       | OFF                                                                                                                    |
#|| secure_file_priv                                  |                                                                                                                        |
#|| server_id                                         | 0                                                                                                                      |
#|| skip_external_locking                             | ON                                                                                                                     |
#|| skip_name_resolve                                 | OFF                                                                                                                    |
skip_networking
#|| skip_show_database                                | OFF                                                                                                                    |
#|| slave_compressed_protocol                         | OFF                                                                                                                    |
#|| slave_exec_mode                                   | STRICT                                                                                                                 |
#|| slave_load_tmpdir                                 | /Users/foobar/.amp/ram_disk/tmp                                                                                        |
#|| slave_max_allowed_packet                          | 1073741824                                                                                                             |
#|| slave_net_timeout                                 | 3600                                                                                                                   |
#|| slave_skip_errors                                 | OFF                                                                                                                    |
#|| slave_transaction_retries                         | 10                                                                                                                     |
#|| slave_type_conversions                            |                                                                                                                        |
#|| slow_launch_time                                  | 2                                                                                                                      |
#|| slow_query_log                                    | OFF                                                                                                                    |
#|| slow_query_log_file                               | /Users/foobar/.amp/ram_disk/mysql/whizbangz-slow.log                                                                   |
#|| socket                                            | /Users/foobar/.amp/ram_disk/tmp/mysqld.sock                                                                            |
#|| sort_buffer_size                                  | 2097152                                                                                                                |
sql_auto_is_null
sql_big_selects
sql_big_tables
sql_log_bin
sql_log_off
sql_low_priority_updates
sql_max_join_size
sql_mode
sql_notes
sql_quote_show_create
sql_safe_updates
sql_select_limit
sql_slave_skip_counter
sql_warnings
#|| ssl_ca                                            |                                                                                                                        |
#|| ssl_capath                                        |                                                                                                                        |
#|| ssl_cert                                          |                                                                                                                        |
#|| ssl_cipher                                        |                                                                                                                        |
#|| ssl_key                                           |                                                                                                                        |
storage_engine
stored_program_cache
#|| sync_binlog                                       | 0                                                                                                                      |
#|| sync_frm                                          | ON                                                                                                                     |
#|| sync_master_info                                  | 0                                                                                                                      |
#|| sync_relay_log                                    | 0                                                                                                                      |
#|| sync_relay_log_info                               | 0                                                                                                                      |
system_time_zone
table_definition_cache
table_open_cache
thread_cache_size
thread_concurrency
thread_handling
thread_stack
time_format
time_zone
timed_mutexes
#|| timestamp                                         | 1449353441                                                                                                             |
tmp_table_size
#|| tmpdir                                            | /Users/foobar/.amp/ram_disk/tmp                                                                                        |
transaction_alloc_block_size
transaction_prealloc_size
tx_isolation
unique_checks
updatable_views_with_limit
version
version_comment
version_compile_machine
version_compile_os
wait_timeout
warning_count
## As a rule of thumb, we include booleans/integer/enum settings
## but omit free-form settings which could include identifying info.
ajaxPopupsEnabled
allowPermDeleteFinancial
backtrace
civimail_multiple_bulk_emails
civimail_server_wide_lock
civimail_workflow
contact_ajax_check_similar
contact_undelete
debug_enabled
disable_core_css
disable_mandatory_tokens_check
editor_id
enableSSL
enable_cart
includeAlphabeticalPager
includeEmailInName
includeNickNameInName
includeOrderByClause
includeWildCardInName
inheritLocale
languageLimit
lcMessages
legacyEncoding
logging
mailThrottleTime
mailerBatchLimit
mailerJobSize
mailerJobsMax
maxFileSize
max_attachments
max_attachments_backend
replyTo
secondDegRelPermissions
securityAlert
smartGroupCacheTimeout
track_civimail_replies
uniq_email_per_site
verifySSL
<?php
/*
 +--------------------------------------------------------------------+
 | Copyright CiviCRM LLC. All rights reserved.                        |
 |                                                                    |
 | This work is published under the GNU AGPLv3 license with some      |
 | permitted exceptions and without any warranty. For full license    |
 | and copyright information, see https://civicrm.org/licensing       |
 +--------------------------------------------------------------------+
 */

/**
 * @package CiviCRM_APIv3
 */

/**
 * Get available api actions.
 *
 * @param array $apiRequest
 *
 * @return array
 * @throws CRM_Core_Exception
 */
function civicrm_api3_generic_getActions($apiRequest) {
  civicrm_api3_verify_mandatory($apiRequest, NULL, ['entity']);
  $mfp = \Civi::service('magic_function_provider');
  $actions = $mfp->getActionNames($apiRequest['version'], $apiRequest['entity']);
  return civicrm_api3_create_success($actions, $apiRequest['params'], $apiRequest['entity'], 'getactions');
}<?php
/*
 +--------------------------------------------------------------------+
 | Copyright CiviCRM LLC. All rights reserved.                        |
 |                                                                    |
 | This work is published under the GNU AGPLv3 license with some      |
 | permitted exceptions and without any warranty. For full license    |
 | and copyright information, see https://civicrm.org/licensing       |
 +--------------------------------------------------------------------+
 */

/**
 * @package CiviCRM_APIv3
 */

/**
 * Generic api wrapper used for quicksearch and autocomplete.
 *
 * @param array $apiRequest
 *
 * @return mixed
 * @throws \CRM_Core_Exception
 */
function civicrm_api3_generic_getList($apiRequest) {
  $entity = CRM_Core_DAO_AllCoreTables::convertEntityNameToLower($apiRequest['entity']);
  $request = $apiRequest['params'];
  $meta = civicrm_api3_generic_getfields(['action' => 'get'] + $apiRequest, FALSE)['values'];

  // If the user types an integer into the search
  $forceIdSearch = empty($request['id']) && !empty($request['input']) && !empty($meta['id']) && CRM_Utils_Rule::positiveInteger($request['input']) && (substr($request['input'], 0, 1) !== '0');
  // Add an extra page of results for the record with an exact id match
  if ($forceIdSearch) {
    $request['page_num'] = ($request['page_num'] ?? 1) - 1;
    $idRequest = $request;
    if (empty($idRequest['page_num'])) {
      $idRequest['id'] = $idRequest['input'];
      unset($idRequest['input']);
    }
    $result = _civicrm_api3_generic_getlist_get_result($idRequest, $entity, $meta, $apiRequest);
  }

  $searchResult = _civicrm_api3_generic_getlist_get_result($request, $entity, $meta, $apiRequest);
  $foundIDCount = 0;
  if ($forceIdSearch && !empty($result['values']) && isset($idRequest['id'])) {
    $contactSearchID = $idRequest['id'];
    $foundIDCount = 1;
    // Merge id fetch into search result.
    foreach ($searchResult['values'] as $searchResultItem) {
      if ($searchResultItem['id'] !== $contactSearchID) {
        $result['values'][] = $searchResultItem;
      }
      else {
        // If the id search found the same contact as the string search then
        // set foundIDCount to 0 - ie no additional row should be added for the id.
        $foundIDCount = 0;
      }
    }
  }
  else {
    $result = $searchResult;
  }
  // Hey api, would you like to format the output?
  $fnName = "_civicrm_api3_{$entity}_getlist_output";
  $fnName = function_exists($fnName) ? $fnName : '_civicrm_api3_generic_getlist_output';
  $values = $fnName($result, $request, $entity, $meta);

  _civicrm_api3_generic_getlist_postprocess($result, $request, $values);

  $output = ['page_num' => $request['page_num']];

  if ($forceIdSearch) {
    $output['page_num']++;
    // When returning the single record matching id
    if (empty($request['page_num'])) {
      foreach ($values as $i => $value) {
        $description = ts('ID: %1', [1 => $value['id']]);
        $values[$i]['description'] = array_merge([$description], $value['description'] ?? []);
      }
    }
  }
  // Limit is set for searching but not fetching by id
  if (!empty($request['params']['options']['limit'])) {
    // If we have an extra result then this is not the last page
    $last = ($request['params']['options']['limit'] - 1) + $foundIDCount;
    $output['more_results'] = isset($values[$last]);
    unset($values[$last]);
  }

  return civicrm_api3_create_success($values, $request['params'], $entity, 'getlist', CRM_Core_DAO::$_nullObject, $output);
}

/**
 * @param string $entity
 * @param $request
 * @param $meta
 * @param array $apiRequest
 *
 * @return array
 * @throws \CRM_Core_Exception
 */
function _civicrm_api3_generic_getlist_get_result(array &$request, string $entity, $meta, array $apiRequest): array {
  // Hey api, would you like to provide default values?
  $fnName = "_civicrm_api3_{$entity}_getlist_defaults";
  $defaults = function_exists($fnName) ? $fnName($request) : [];
  _civicrm_api3_generic_getList_defaults($entity, $request, $defaults, $meta);

  // Hey api, would you like to format the search params?
  $fnName = "_civicrm_api3_{$entity}_getlist_params";
  $fnName = function_exists($fnName) ? $fnName : '_civicrm_api3_generic_getlist_params';
  $fnName($request);

  $request['params']['check_permissions'] = !empty($apiRequest['params']['check_permissions']);
  $result = civicrm_api3($entity, 'get', $request['params']);
  if (!empty($request['input']) && !empty($defaults['search_field_fallback']) && $result['count'] < $request['params']['options']['limit']) {
    // We support a field fallback. Note we don't do this as an OR query because that could easily
    // bypass an index & kill the server. We just 'pad' the results if needed with the second
    // query - this is effectively the same as what the old Ajax::getContactEmail function did.
    // Since these queries should be quick & often only one should be needed this is a simpler alternative
    // to constructing a UNION via the api.
    $request['params'][$defaults['search_field_fallback']] = $request['params'][$defaults['search_field']];
    if ($request['params']['options']['sort'] === $defaults['search_field']) {
      // The way indexing works here is that the order by field will be chosen in preference to the
      // filter field. This can result in really bad performance so use the filter field for the sort.
      // See https://github.com/civicrm/civicrm-core/pull/16993 for performance test results.
      $request['params']['options']['sort'] = $defaults['search_field_fallback'];
    }
    // Exclude anything returned from the previous query since we are looking for additional rows in this
    // second query.
    $request['params'][$defaults['search_field']] = ['NOT LIKE' => $request['params'][$defaults['search_field_fallback']]['LIKE']];
    $request['params']['options']['limit'] -= $result['count'];
    $result2 = civicrm_api3($entity, 'get', $request['params']);
    $result['values'] = array_merge($result['values'], $result2['values']);
    $result['count'] = count($result['values']);
  }
  else {
    // Re-index to sequential = 0.
    $result['values'] = array_merge($result['values']);
  }
  return $result;
}

/**
 * Set defaults for api.getlist.
 *
 * @param string $entity
 * @param array $request
 * @param array $apiDefaults
 * @param array $fields
 */
function _civicrm_api3_generic_getList_defaults(string $entity, array &$request, array $apiDefaults, array $fields): void {
  $defaults = [
    'page_num' => 1,
    'input' => '',
    'image_field' => NULL,
    'color_field' => isset($fields['color']) ? 'color' : NULL,
    'id_field' => $entity === 'option_value' ? 'value' : 'id',
    'description_field' => [],
    'add_wildcard' => Civi::settings()->get('includeWildCardInName'),
    'params' => [],
    'extra' => [],
  ];
  // Find main field from meta
  foreach (['sort_name', 'title', 'label', 'name', 'subject'] as $field) {
    if (isset($fields[$field])) {
      $defaults['label_field'] = $defaults['search_field'] = $field;
      break;
    }
  }
  // Find fields to be used for the description
  foreach (['description'] as $field) {
    if (isset($fields[$field])) {
      $defaults['description_field'][] = $field;
    }
  }
  $resultsPerPage = Civi::settings()->get('search_autocomplete_count');
  if (isset($request['params']) && isset($apiDefaults['params'])) {
    $request['params'] += $apiDefaults['params'];
  }
  $request += $apiDefaults + $defaults;
  // Default api params
  $params = [
    'sequential' => 0,
    'options' => [],
  ];
  // When searching e.g. autocomplete
  if ($request['input']) {
    $params[$request['search_field']] = ['LIKE' => ($request['add_wildcard'] ? '%' : '') . $request['input'] . '%'];
  }
  $request['params'] += $params;

  // When looking up a field e.g. displaying existing record
  if (!empty($request['id'])) {
    if (is_string($request['id']) && strpos($request['id'], ',')) {
      $request['id'] = explode(',', trim($request['id'], ', '));
    }
    // Don't run into search limits when prefilling selection
    $request['params']['options']['limit'] = NULL;
    unset($request['params']['options']['offset']);
    $request['params'][$request['id_field']] = is_array($request['id']) ? ['IN' => $request['id']] : $request['id'];
  }
  else {
    $request['params']['options'] += [
      // Add pagination parameters
      'sort' => $request['label_field'],
      // Adding one extra result allows us to see if there are any more
      'limit' => $resultsPerPage + 1,
      // Because sql is zero-based
      'offset' => ($request['page_num'] > 1) ? (($request['page_num'] - 1) * $resultsPerPage) : 0,
    ];
  }
}

/**
 * Fallback implementation of getlist_params. May be overridden by individual apis.
 *
 * @param array $request
 */
function _civicrm_api3_generic_getlist_params(&$request) {
  $fieldsToReturn = [$request['id_field'], $request['label_field']];
  if (!empty($request['image_field'])) {
    $fieldsToReturn[] = $request['image_field'];
  }
  if (!empty($request['color_field'])) {
    $fieldsToReturn[] = $request['color_field'];
  }
  if (!empty($request['description_field'])) {
    $fieldsToReturn = array_merge($fieldsToReturn, (array) $request['description_field']);
  }
  $request['params']['return'] = array_unique(array_merge($fieldsToReturn, $request['extra']));
}

/**
 * Fallback implementation of getlist_output. May be overridden by individual api functions.
 *
 * @param array $result
 * @param array $request
 * @param string $entity
 * @param array $fields
 *
 * @return array
 */
function _civicrm_api3_generic_getlist_output($result, $request, $entity, $fields) {
  $output = [];
  if (!empty($result['values'])) {
    foreach ($result['values'] as $row) {
      $data = [
        'id' => $row[$request['id_field']],
        'label' => $row[$request['label_field']],
      ];
      if (!empty($request['description_field'])) {
        $data['description'] = [];
        foreach ((array) $request['description_field'] as $field) {
          if (!empty($row[$field])) {
            if (!isset($fields[$field]['pseudoconstant'])) {
              $data['description'][] = $row[$field];
            }
            else {
              $data['description'][] = CRM_Core_PseudoConstant::getLabel(
                _civicrm_api3_get_BAO($entity),
                $field,
                $row[$field]
              );
            }
          }
        }
      }
      if (!empty($request['image_field'])) {
        $data['image'] = $row[$request['image_field']] ?? '';
      }
      if (isset($row[$request['color_field']])) {
        $data['color'] = $row[$request['color_field']];
      }
      $output[] = $data;
    }
  }
  return $output;
}

/**
 * Common postprocess for getlist output
 *
 * @param array $result
 * @param array $request
 * @param array $values
 */
function _civicrm_api3_generic_getlist_postprocess($result, $request, &$values) {
  $chains = [];
  foreach ($request['params'] as $field => $param) {
    if (substr($field, 0, 4) === 'api.') {
      $chains[] = $field;
    }
  }
  if (!empty($result['values'])) {
    foreach (array_values($result['values']) as $num => $row) {
      foreach ($request['extra'] as $field) {
        $values[$num]['extra'][$field] = $row[$field] ?? NULL;
      }
      foreach ($chains as $chain) {
        $values[$num][$chain] = $row[$chain] ?? NULL;
      }
    }
  }
}

/**
 * Provide metadata for this api
 *
 * @param array $params
 * @param array $apiRequest
 */
function _civicrm_api3_generic_getlist_spec(&$params, $apiRequest) {
  $params += [
    'page_num' => [
      'title' => 'Page Number',
      'description' => "Current page of a multi-page lookup",
      'type' => CRM_Utils_Type::T_INT,
    ],
    'input' => [
      'title' => 'Search Input',
      'description' => "String to search on",
      'type' => CRM_Utils_Type::T_TEXT,
    ],
    'params' => [
      'title' => 'API Params',
      'description' => "Additional filters to send to the {$apiRequest['entity']} API.",
    ],
    'extra' => [
      'title' => 'Extra',
      'description' => 'Array of additional fields to return.',
    ],
    'image_field' => [
      'title' => 'Image Field',
      'description' => "Field that this entity uses to store icons (usually automatic)",
      'type' => CRM_Utils_Type::T_TEXT,
    ],
    'id_field' => [
      'title' => 'ID Field',
      'description' => "Field that uniquely identifies this entity (usually automatic)",
      'type' => CRM_Utils_Type::T_TEXT,
    ],
    'description_field' => [
      'title' => 'Description Field',
      'description' => "Field that this entity uses to store summary text (usually automatic)",
      'type' => CRM_Utils_Type::T_TEXT,
    ],
    'label_field' => [
      'title' => 'Label Field',
      'description' => "Field to display as title of results (usually automatic)",
      'type' => CRM_Utils_Type::T_TEXT,
    ],
    'search_field' => [
      'title' => 'Search Field',
      'description' => "Field to search on (assumed to be the same as label field unless otherwise specified)",
      'type' => CRM_Utils_Type::T_TEXT,
    ],
  ];
}<?php
/*
 +--------------------------------------------------------------------+
 | Copyright CiviCRM LLC. All rights reserved.                        |
 |                                                                    |
 | This work is published under the GNU AGPLv3 license with some      |
 | permitted exceptions and without any warranty. For full license    |
 | and copyright information, see https://civicrm.org/licensing       |
 +--------------------------------------------------------------------+
 */

/**
 * @package CiviCRM_APIv3
 */

/**
 * Generic api wrapper used to get all unique fields for a given entity.
 *
 * @param array $apiRequest
 *
 * @return mixed
 */
function civicrm_api3_generic_getunique($apiRequest) {
  $entity = _civicrm_api_get_entity_name_from_camel($apiRequest['entity']);
  $uniqueFields = [];

  $dao = _civicrm_api3_get_DAO($entity);
  $uFields = $dao::indices();

  foreach ($uFields as $fieldKey => $field) {
    if (!isset($field['unique']) || !$field['unique']) {
      continue;
    }
    $uniqueFields[$fieldKey] = $field['field'];
  }

  return civicrm_api3_create_success($uniqueFields);
}<?php
/*
 +--------------------------------------------------------------------+
 | Copyright CiviCRM LLC. All rights reserved.                        |
 |                                                                    |
 | This work is published under the GNU AGPLv3 license with some      |
 | permitted exceptions and without any warranty. For full license    |
 | and copyright information, see https://civicrm.org/licensing       |
 +--------------------------------------------------------------------+
 */

/**
 * @package CiviCRM_APIv3
 */

/**
 * Set a single value using the api.
 *
 * This function is called when no specific setvalue api exists.
 * Params must contain at least id=xx & {one of the fields from getfields}=value
 *
 * @param array $apiRequest
 *
 * @throws CRM_Core_Exception
 * @return array
 */
function civicrm_api3_generic_setValue($apiRequest) {
  $entity = $apiRequest['entity'];
  $params = $apiRequest['params'];
  $id = $params['id'];
  if (!is_numeric($id)) {
    return civicrm_api3_create_error(ts('Please enter a number'), [
      'error_code' => 'NaN',
      'field' => "id",
    ]);
  }

  $field = CRM_Utils_String::munge($params['field']);
  $value = $params['value'];

  $fields = civicrm_api($entity, 'getFields', [
    'version' => 3,
    'action' => 'create',
  ]);
  // getfields error, shouldn't happen.
  if ($fields['is_error']) {
    return $fields;
  }
  $fields = $fields['values'];

  $isCustom = strpos($field, 'custom_') === 0;
  // Trim off the id portion of a multivalued custom field name
  $fieldKey = $isCustom && substr_count($field, '_') > 1 ? rtrim(rtrim($field, '1234567890'), '_') : $field;
  if (!array_key_exists($fieldKey, $fields)) {
    return civicrm_api3_create_error("Param 'field' ($field) is invalid. must be an existing field", ["error_code" => "invalid_field", "fields" => array_keys($fields)]);
  }

  $def = $fields[$fieldKey];
  $title = $def['title'] ?? ts('Field');
  // Disallow empty values except for the number zero.
  // TODO: create a utility for this since it's needed in many places
  if (!empty($def['required']) || !empty($def['is_required'])) {
    if ((empty($value) || $value === 'null') && $value !== '0' && $value !== 0) {
      return civicrm_api3_create_error(ts('%1 is a required field.', [1 => $title]), ["error_code" => "required", "field" => $field]);
    }
  }

  switch ($def['type']) {
    case CRM_Utils_Type::T_FLOAT:
      if (!is_numeric($value) && !empty($value) && $value !== 'null') {
        return civicrm_api3_create_error(ts('%1 must be a number.', [1 => $title]), ['error_code' => 'NaN']);
      }
      break;

    case CRM_Utils_Type::T_INT:
      if (!CRM_Utils_Rule::integer($value) && !empty($value) && $value !== 'null') {
        return civicrm_api3_create_error(ts('%1 must be a number.', [1 => $title]), ['error_code' => 'NaN']);
      }
      break;

    case CRM_Utils_Type::T_STRING:
    case CRM_Utils_Type::T_TEXT:
      if (array_key_exists('maxlength', $def)) {
        $value = substr($value, 0, $def['maxlength']);
      }
      break;

    case CRM_Utils_Type::T_DATE:
      $value = CRM_Utils_Type::escape($value, "Date", FALSE);
      if (!$value) {
        return civicrm_api3_create_error("Param '$field' is not a date. format YYYYMMDD or YYYYMMDDHHMMSS");
      }
      break;

    case CRM_Utils_Type::T_BOOLEAN:
      // Allow empty value for non-required fields
      if ($value === '' || $value === 'null') {
        $value = '';
      }
      else {
        $value = (boolean) $value;
      }
      break;

    default:
      return civicrm_api3_create_error("Param '$field' is of a type not managed yet (" . $def['type'] . "). Join the API team and help us implement it", ['error_code' => 'NOT_IMPLEMENTED']);
  }

  $dao_name = _civicrm_api3_get_DAO($entity);
  $params = ['id' => $id, $field => $value];

  if ((!empty($def['pseudoconstant']) || !empty($def['option_group_id'])) && $value !== '' && $value !== 'null') {
    _civicrm_api3_api_match_pseudoconstant($params[$field], $entity, $field, $def);
  }

  CRM_Utils_Hook::pre('edit', $entity, $id, $params);

  // Custom fields
  if ($isCustom) {
    CRM_Utils_Array::crmReplaceKey($params, 'id', 'entityID');
    // Treat 'null' as empty value. This is awful but the rest of the code supports it.
    if ($params[$field] === 'null') {
      $params[$field] = '';
    }
    CRM_Core_BAO_CustomValueTable::setValues($params);
    CRM_Utils_Hook::post('edit', $entity, $id);
  }
  // Core fields
  elseif (CRM_Core_DAO::setFieldValue($dao_name, $id, $field, $params[$field])) {
    $entityDAO = new $dao_name();
    $entityDAO->copyValues($params);
    CRM_Utils_Hook::post('edit', $entity, $entityDAO->id, $entityDAO);
  }
  else {
    return civicrm_api3_create_error("error assigning $field=$value for $entity (id=$id)");
  }

  // Add changelog entry - TODO: Should we do this for other entities as well?
  if (strtolower($entity) === 'contact') {
    CRM_Core_BAO_Log::register($id, 'civicrm_contact', $id);
  }

  return civicrm_api3_create_success($params);
}<?php
/*
 +--------------------------------------------------------------------+
 | Copyright CiviCRM LLC. All rights reserved.                        |
 |                                                                    |
 | This work is published under the GNU AGPLv3 license with some      |
 | permitted exceptions and without any warranty. For full license    |
 | and copyright information, see https://civicrm.org/licensing       |
 +--------------------------------------------------------------------+
 */

/**
 * @package CiviCRM_APIv3
 */

/**
 * Update function is basically a hack.
 *
 * We want to remove it but must resolve issues in
 * http://issues.civicrm.org/jira/browse/CRM-12144
 *
 * It is not recommended & if update doesn't work & fix does then update will not be fixed
 *
 * To do this, perform a 'get' action to load the existing values, then merge in the updates
 * and call 'create' to save the revised entity.
 *
 * @deprecated
 *
 * @param array $apiRequest
 *   Array with keys:
 *   - entity: string
 *   - action: string
 *   - version: string
 *   - function: callback (mixed)
 *   - params: array, varies
 *
 * @return array|int|mixed
 */
function civicrm_api3_generic_update($apiRequest) {
  //$key_id = strtolower ($apiRequest['entity'])."_id";
  $key_id = "id";
  if (!array_key_exists($key_id, $apiRequest['params'])) {
    return civicrm_api3_create_error("Mandatory parameter missing $key_id");
  }
  // @fixme
  // tests show that contribution works better with create
  // this is horrible but to make it work we'll just handle it separately
  if (strtolower($apiRequest['entity']) == 'contribution') {
    return civicrm_api($apiRequest['entity'], 'create', $apiRequest['params']);
  }
  $seek = [$key_id => $apiRequest['params'][$key_id], 'version' => $apiRequest['version']];
  $existing = civicrm_api($apiRequest['entity'], 'get', $seek);
  if ($existing['is_error']) {
    return $existing;
  }
  if ($existing['count'] > 1) {
    return civicrm_api3_create_error("More than one " . $apiRequest['entity'] . " with id " . $apiRequest['params'][$key_id]);
  }
  if ($existing['count'] == 0) {
    return civicrm_api3_create_error("No " . $apiRequest['entity'] . " with id " . $apiRequest['params'][$key_id]);
  }

  $existing = array_pop($existing['values']);
  // Per Unit test testUpdateHouseholdWithAll we don't want to load these from the DB
  // if they are not passed in then we'd rather they are calculated.
  // Note update is not recomended anyway...
  foreach (['sort_name', 'display_name'] as $fieldToNotSet) {
    unset($existing[$fieldToNotSet]);
  }
  $p = array_merge($existing, $apiRequest['params']);
  return civicrm_api($apiRequest['entity'], 'create', $p);
}<?php
/*
 +--------------------------------------------------------------------+
 | Copyright CiviCRM LLC. All rights reserved.                        |
 |                                                                    |
 | This work is published under the GNU AGPLv3 license with some      |
 | permitted exceptions and without any warranty. For full license    |
 | and copyright information, see https://civicrm.org/licensing       |
 +--------------------------------------------------------------------+
 */

/**
 * @package CiviCRM_APIv3
 */

/**
 * Provide meta-data for this api.
 *
 * @param array $params
 */
function _civicrm_api3_generic_validate_spec(&$params) {
  $params['action']['api.required'] = TRUE;
  $params['action']['title'] = ts('API Action');
}

/**
 * Generic api wrapper used for validation of entity-action pair.
 *
 * @param array $apiRequest
 *
 * @return mixed
 */
function civicrm_api3_generic_validate($apiRequest) {
  $errors = _civicrm_api3_validate($apiRequest['entity'], $apiRequest['params']['action'], $apiRequest['params']);

  return civicrm_api3_create_success($errors, $apiRequest['params'], $apiRequest['entity'], 'validate');
}