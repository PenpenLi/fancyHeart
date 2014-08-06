package com.doteyplay;

import java.io.InputStream;
import java.util.Properties;

import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;

import com.doteyplay.core.dbcs.DBCS;
import com.doteyplay.dao.IUserBeanDao;
import com.doteyplay.manager.AreaManager;
import com.doteyplay.manager.AuthManager;
import com.doteyplay.manager.NosqlCached;
import com.doteyplay.net.NetServer;

public class ServiceContext implements ServletContextListener
{
	
	private static NetServer netServer;
	
	@Override
	public void contextInitialized(ServletContextEvent arg0)
	{
		DBCS.initialize("/db/");
		try
		{
			try
			{
				InputStream tmpIn = CommonConfig.class.getResourceAsStream("/conf/server.properties");
				Properties cfgProperties = new Properties();
				cfgProperties.load(tmpIn);
				
				CommonConfig.PORT = Integer.parseInt(cfgProperties.getProperty("port"));
				CommonConfig.REDIS_PORT = Integer.parseInt(cfgProperties.getProperty("redis_port"));
				CommonConfig.REDIS_IP = cfgProperties.getProperty("redis_ip");

			}
			catch (Exception e)
			{
				e.printStackTrace();
			}

			NetServer.getInstance().init();
			NosqlCached.getInstance().init();
			AreaManager.getInstance().init();
			
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}

	public static NetServer getNetServer()
	{
		return netServer;
	}
	
	@Override
	public void contextDestroyed(ServletContextEvent arg0)
	{
		
	}
}