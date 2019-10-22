package com.cordova.plugins;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.util.Log;
import android.content.Context;

import com.simility.recon.SimilityScript;
import com.simility.recon.SimilityContext;

public class DeviceRecon extends CordovaPlugin  {
    private String customerId, sessionId, userId; 
    private static final String ACTION = "signal";
    private static final String TAG = "DEVICE_RECON";
    private static final String SUCCESS = "Success";
    
    @Override
    public boolean execute(String action, JSONArray args,
                           CallbackContext callbackContext) throws JSONException {

        JSONObject obj =  new JSONObject(args.getString(0));

        if (action.equals(ACTION)) {
            if(args.length() != 0){
                customerId = obj.getString("customer_id");
                sessionId = obj.getString("session_id");
                if(obj.has("user_id"))
                    userId = obj.getString("user_id");
            }

            try {
                Context context = this.cordova.getActivity().getApplicationContext();
                SimilityContext similityContext = new SimilityContext();
                similityContext.setApplicationContext(context);
                similityContext.setCustomerId(customerId);
                similityContext.setSessionId(sessionId);
                similityContext.setUserId(userId);

                SimilityScript.getInstance().execute(similityContext);
                callbackContext.success(SUCCESS);
                return true;
            } catch (Exception e) {
                callbackContext.error(e.toString());
            }            
        }
        return false; 
    }
}